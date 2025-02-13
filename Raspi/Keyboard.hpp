#ifndef __KEYBOARD_HPP
#define __KEYBOARD_HPP

#include "Config.hpp"
#include <memory>
#include <cstdint>

class Keyboard {
private:
	std::shared_ptr<KeyboardConfig> config;

public:
	Keyboard(const std::shared_ptr<KeyboardConfig>& config);

	void Setup();

	enum class KeyType : uint8_t {
		NONE,
		UNICODE,
		KEYCODE
	};
	struct KeyResult {
		KeyType type;
		char32_t codepoint;
		char8_t keycode;
	};
	KeyResult GetKey();
};

#endif // __KEYBOARD_HPP
