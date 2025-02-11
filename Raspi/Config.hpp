#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include <string>
#include <map>
#include <cstdint>

class Config {
public:


	Config(const std::string& path);
};

class KeyboardConfig {
private:
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

	std::map<MatrixPos, uint8_t> modMap;
	std::map<KeyboardKey, char32_t> codepointMap;
	std::map<KeyboardKey, char8_t> keyMap;

public:
	KeyboardConfig(const std::string& path);
};

#endif // __CONFIG_HPP
