#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>

static constexpr const uint8_t MOD_NONE = 0x00;
static constexpr const uint8_t MOD_SHFT = 0x01;
static constexpr const uint8_t MOD_CODE = 0x02;

class KeyboardConfig {
public:
	struct MatrixPos {
		uint8_t scan;
		uint8_t out;

		bool operator<(const MatrixPos& rhs) const {
			return
				(scan < rhs.scan)
				|| (scan == rhs.scan && out < rhs.out);
		}
	};

	struct KeyboardKey {
		MatrixPos pos;
		uint8_t mod;

		bool operator<(const KeyboardKey& rhs) const {
			return
				(pos.scan < rhs.pos.scan)
				|| (pos.scan == rhs.pos.scan && pos.out < rhs.pos.out)
				|| (pos.scan == rhs.pos.scan && pos.out == rhs.pos.out && mod < rhs.mod);
		}
	};

	std::vector<int> pinsScan;
	std::vector<int> pinsOut;
	std::map<MatrixPos, uint8_t> modMap;
	std::map<KeyboardKey, char32_t> codepointMap;
	std::map<KeyboardKey, char8_t> keyMap;

	KeyboardConfig(const std::string& path);
};

class PrinterConfig {
public:
	struct SerialSettings {
		std::string port;
		int baud;
	};

	SerialSettings serial;

	PrinterConfig(const std::string& path);
};

class TerminalConfig {
public:
	struct WindowSettings {
		unsigned short columns;
		unsigned short rows;
	};

	struct ShellSettings {
		std::string binary;
		std::vector<std::string> arguments;
	};

	std::vector<std::string> environment;
	WindowSettings window;
	ShellSettings shell;

	TerminalConfig(const std::string& path);
};

#endif // __CONFIG_HPP
