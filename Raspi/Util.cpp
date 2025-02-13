#include "Util.hpp"

#include <cstring>
#include <sstream>
#include <stdexcept>

void Util::ThrowErrno() {
	error_t e = errno;
	errno = 0;
	std::string msg = std::string(strerror(errno));
	if (errno != 0) {
		msg = "failed to retrieve error string. Errno value: ";
		msg += e;
	}
	throw std::runtime_error(msg);
}

uint8_t Util::UTF8GetByteLength(char8_t firstByte) {
	uint8_t size = 0;
	if ((firstByte & 0b1000'0000) == 0b0000'0000)
		size = 1;
	else if ((firstByte & 0b1110'0000) == 0b1100'0000)
		size = 2;
	else if ((firstByte & 0b1111'0000) == 0b1110'0000)
		size = 3;
	else if ((firstByte & 0b1111'1000) == 0b1111'0000)
		size = 4;
	else {
		std::stringstream ss;
		ss << "invalid UTF-8 starting Byte 0x" << std::hex << static_cast<int>(firstByte);
		throw std::runtime_error(ss.str());
	}
	return size;
}

char32_t Util::UTF8GetCodepoint(const char8_t* buffer, uint8_t length) {
	char32_t codepoint = 0;

	if (buffer == nullptr || length < 1 || length > 4) return codepoint;

	static char8_t fbMasks[] = { 0b0111'1111, 0b0001'1111, 0b0000'1111, 0b0000'0111 };
	codepoint = buffer[0] & fbMasks[length - 1];

	for (uint8_t i = 1; i < length; i++) {
		if ((buffer[i] & 0b1100'0000) != 0b1000'0000) {
			std::stringstream ss;
			ss << "invalid UTF-8 continuation Byte 0x" << std::hex << static_cast<int>(buffer[i])
				<< " in sequence [";
			for (uint8_t k = 0; k < length; k++) {
				ss << " 0x" << std::hex << static_cast<int>(buffer[k]);
			}
			ss << " ] with length " << std::dec << static_cast<int>(length);
			throw std::runtime_error(ss.str());
		}
		codepoint <<= 6;
		codepoint |= buffer[i] & 0b0011'1111;
	}

	return codepoint;
}

uint8_t Util::CodepointGetUTF8(char32_t codepoint, char8_t* buffer) {
	uint8_t length = 0;

	if (codepoint >= 0x0000'0000 && codepoint <= 0x0000'007F) {
		buffer[0] = codepoint;
		length = 1;
	}
	else if (codepoint >= 0x0000'0080 && codepoint <= 0x0000'07FF) {
		buffer[0] = (codepoint >> 8) & 0x1F;
		buffer[1] = codepoint & 0x3F;
		length = 2;
	}
	else if (codepoint >= 0x0000'0800 && codepoint <= 0x0000'7FFF) {
		buffer[0] = (codepoint >> 16) & 0x0F;
		buffer[1] = (codepoint >> 8) & 0x3F;
		buffer[2] = codepoint & 0x3F;
		length = 3;
	}
	else if (codepoint >= 0x0001'0000 && codepoint <= 0x0010'FFFF) {
		buffer[0] = (codepoint >> 24) & 0x07;
		buffer[1] = (codepoint >> 16) & 0x3F;
		buffer[2] = (codepoint >> 8) & 0x3F;
		buffer[3] = codepoint & 0x3F;
		length = 4;
	}
	else {
		std::stringstream ss;
		ss << "invalid unicode codepoint U+" << std::hex << static_cast<uint32_t>(codepoint);
		throw std::runtime_error(ss.str());
	}

	return length;
}
