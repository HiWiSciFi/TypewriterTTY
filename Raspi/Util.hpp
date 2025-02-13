#ifndef __UTIL_HPP
#define __UTIL_HPP

#include <cstdint>

class Util {
public:
	static void ThrowErrno();

	static uint8_t UTF8GetByteLength(char8_t firstByte);
	static char32_t UTF8GetCodepoint(const char8_t* buffer, uint8_t length);
	
	// buffer must be at least 4 chars big
	static uint8_t CodepointGetUTF8(char32_t codepoint, char8_t* buffer);
};

#endif // __UTIL_HPP
