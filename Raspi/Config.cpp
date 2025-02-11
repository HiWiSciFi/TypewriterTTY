#include "Config.hpp"

#include <map>
#include <string>
#include <toml.hpp>

#include <iostream>

Config::Config(const std::string& path) {
	toml::value data = toml::parse(path, toml::spec::v(1, 1, 0));

	// auto val = toml::find<std::map<std::string, std::string>>(data, "mod");
	// std::cout << data.at("mod").at("9").at("7").as_string() << std::endl;
	auto table = data.as_table();

	for (const auto& kv : table) {
		std::cout << kv.first << std::endl;
	}
}

static const constexpr uint8_t MOD_NONE = 0x00;
static const constexpr uint8_t MOD_SHFT = 0x01;
static const constexpr uint8_t MOD_CODE = 0x02;

KeyboardConfig::KeyboardConfig(const std::string& path) {
	toml::value data = toml::parse(path, toml::spec::v(1, 1, 0));
	auto fileMap = data.as_table();

	for (const auto& section : fileMap) {
		if (section.first == "mod") {
			for (const auto& scanSec : section.second.as_table()) {
				uint8_t scan = std::stoi(scanSec.first);
				for (const auto& outSec : scanSec.second.as_table()) {
					uint8_t out = std::stoi(outSec.first);
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
