#include "Config.hpp"

// File note: maybe generically generate the possible mod keys for the keyboard configuration from
//            the entries in the mod section

// TODO: rewrite keyboard config loading

#include "Util.hpp"

#include <cstring>
#include <map>
#include <sstream>
#include <string>
#include <toml.hpp>

PrinterConfig::PrinterConfig(const std::string& path) {
	auto fileMap = toml::parse(path, toml::spec::v(1, 1, 0)).as_table();

	auto serialSection = fileMap.at("serial");
	this->serial.port = serialSection.at("port").as_string();
	this->serial.baud = serialSection.at("baud").as_integer();

	auto printerSection = fileMap.at("printer").as_table();
	this->printer.translationFallback = printerSection.at("translation fallback").as_integer();

	auto codepointSection = fileMap.at("translation").as_table();
	for (const auto& te : codepointSection) {
		if (te.first.length() < 1)
			throw std::runtime_error("invalid toml key");
		uint8_t length = Util::UTF8GetByteLength(te.first.at(0));
		if (te.first.length() != length)
			throw std::runtime_error("invalid translation map key");
		char32_t codepoint = Util::UTF8GetCodepoint(reinterpret_cast<const char8_t*>(te.first.data()), length);
		
		auto charArray = te.second.as_array();
		std::u8string str;
		str.resize(charArray.size());
		for (size_t i = 0; i < charArray.size(); i++) {
			str.data()[i] = charArray.at(i).as_integer();
		}

		this->translationMap.insert({ codepoint, str });
	}
}

KeyboardConfig::KeyboardConfig(const std::string& path) {
	auto fileMap = toml::parse(path, toml::spec::v(1, 1, 0)).as_table();

	for (const auto& section : fileMap) {
		if (section.first == "pins") {
			this->pinsScan = toml::get<std::vector<int>>(section.second.at("scan"));
			this->pinsOut = toml::get<std::vector<int>>(section.second.at("out"));
		}
		else if (section.first == "mod") {
			for (const auto& scanSec : section.second.as_table()) {
				uint8_t scan = std::stoi(scanSec.first);
				for (const auto& outSec : scanSec.second.as_table()) {
					uint8_t out = std::stoi(outSec.first);
					uint8_t mod = MOD_NONE;
					if (outSec.first == "NONE") mod = MOD_NONE;
					else if (outSec.first == "SHFT") mod = MOD_SHFT;
					else if (outSec.first == "CODE") mod = MOD_CODE;
					this->modMap.insert({ { scan, out }, mod });
				}
			}
		}
		else if (section.first == "codepoint") {
			for (const auto& scanSec : section.second.as_table()) {
				uint8_t scan = std::stoi(scanSec.first);
				for (const auto& outSec : scanSec.second.as_table()) {
					uint8_t out = std::stoi(outSec.first);
					for (const auto& modSec : outSec.second.as_table()) {
						uint8_t mod = MOD_NONE;
						if (modSec.first == "NONE") mod = MOD_NONE;
						else if (modSec.first == "SHFT") mod = MOD_SHFT;
						else if (modSec.first == "CODE") mod = MOD_CODE;
						uint32_t codepoint = modSec.second.as_integer();
						this->codepointMap.insert({ { { scan, out }, mod }, codepoint });
					}
				}
			}
		}
		else if (section.first == "key") {
			for (const auto& scanSec : section.second.as_table()) {
				uint8_t scan = std::stoi(scanSec.first);
				for (const auto& outSec : scanSec.second.as_table()) {
					uint8_t out = std::stoi(outSec.first);
					for (const auto& modSec : outSec.second.as_table()) {
						uint8_t mod = MOD_NONE;
						if (modSec.first == "NONE") mod = MOD_NONE;
						else if (modSec.first == "SHFT") mod = MOD_SHFT;
						else if (modSec.first == "CODE") mod = MOD_CODE;
						char8_t keycode = modSec.second.as_integer();
						this->keyMap.insert({ { { scan, out }, mod }, keycode });
					}
				}
			}
		}
	}
}

TerminalConfig::TerminalConfig(const std::string& path) {
	auto fileMap = toml::parse(path, toml::spec::v(1, 1, 0)).as_table();

	auto environmentSection = fileMap.at("environment").as_table();
	bool inherit = environmentSection.at("env_inherit").as_boolean();

	size_t reserve = 0;
	for (; inherit && environ[reserve] != nullptr; reserve++);
	reserve += environmentSection.size() - 1;
	this->environment.reserve(reserve);

	if (inherit) {
		for (size_t i = 0; environ[i] != nullptr; i++) {
			size_t offset = strcspn(environ[i], "=");
			char var[offset + 1];
			strncpy(var, environ[i], offset);
			var[offset] = '\0';
			if (environmentSection.contains(var)) continue;
			this->environment.push_back(environ[i]);
		}
	}

	for (const auto& entry : environmentSection) {
		if (entry.first == "env_inherit") continue;
		std::stringstream ss;
		ss << entry.first << '=' << entry.second.as_string();
		this->environment.push_back(ss.str());
	}

	auto windowSection = fileMap.at("window").as_table();
	this->window.columns = windowSection.at("columns").as_integer();
	this->window.rows = windowSection.at("rows").as_integer();

	auto shellSection = fileMap.at("shell").as_table();
	this->shell.binary = shellSection.at("binary").as_string();
	this->shell.arguments = toml::get<std::vector<std::string>>(shellSection.at("arguments"));
}
