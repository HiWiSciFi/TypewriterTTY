#ifndef __KEYBOARD_HPP
#define __KEYBOARD_HPP

#include <cstdint>
#include <map>
#include <vector>

struct KeymapEntry {
	uint32_t codepoint;
	uint8_t key;

	inline bool operator==(const KeymapEntry& ke) const {
		return ke.codepoint == this->codepoint
			&& ke.key == this->key;
	}
};

struct KeymapKey {
	int scan;
	int out;
	uint8_t mod;

	bool operator<(const KeymapKey& rhs) const {
		return
			(scan < rhs.scan)
			|| (scan == rhs.scan && out < rhs.out)
			|| (scan == rhs.scan && out == rhs.out && mod < rhs.mod);
	}
};

class Keyboard final {
private:
	std::vector<int> pinsScan;
	std::vector<int> pinsOut;

	static bool initialized;
	void setupPins();

public:
	Keyboard(const std::vector<int>& pinsScan, const std::vector<int>& pinsOut);
	KeymapEntry readKey();
};

static constexpr uint8_t MOD_NONE = 0x00;
static constexpr uint8_t MOD_SHIFT = 0x01;
static constexpr uint8_t MOD_CODE = 0x02;

static std::map<KeymapKey, uint8_t> modkeymap = {
	{ { 8, 6, MOD_NONE }, MOD_SHIFT }, // SHIFT L R
	{ { 0, 3, MOD_NONE }, MOD_CODE  }, // CODE
	{ { 1, 0, MOD_NONE }, MOD_NONE  }, // Case Open
};

static std::map<KeymapKey, KeymapEntry> keymap = {
	{ { 6, 7, MOD_NONE  }, { 0x08, 0x00 } }, // Backspace

	{ { 7, 7, MOD_NONE  }, { 0x20, 0x00 } }, // SPACE
	{ { 2, 0, MOD_SHIFT }, { 0x21, 0x00 } }, // !
	{ { 2, 1, MOD_SHIFT }, { 0x22, 0x00 } }, // "
	{ { 6, 5, MOD_NONE  }, { 0x23, 0x00 } }, // #
	{ { 3, 1, MOD_SHIFT }, { 0x24, 0x00 } }, // $
	{ { 4, 0, MOD_SHIFT }, { 0x25, 0x00 } }, // %
	{ { 4, 1, MOD_SHIFT }, { 0x26, 0x00 } }, // &
	{ { 6, 5, MOD_SHIFT }, { 0x27, 0x00 } }, // '
	{ { 5, 1, MOD_SHIFT }, { 0x28, 0x00 } }, // (
	{ { 6, 0, MOD_SHIFT }, { 0x29, 0x00 } }, // )
	{ { 7, 3, MOD_SHIFT }, { 0x2A, 0x00 } }, // *
	{ { 7, 3, MOD_NONE  }, { 0x2B, 0x00 } }, // +
	{ { 4, 7, MOD_NONE  }, { 0x2C, 0x00 } }, // ,
	{ { 5, 7, MOD_NONE  }, { 0x2D, 0x00 } }, // -
	{ { 5, 6, MOD_NONE  }, { 0x2E, 0x00 } }, // .
	{ { 5, 0, MOD_SHIFT }, { 0x2F, 0x00 } }, // /
	{ { 6, 1, MOD_NONE  }, { 0x30, 0x00 } }, // 0
	{ { 2, 0, MOD_NONE  }, { 0x31, 0x00 } }, // 1
	{ { 2, 1, MOD_NONE  }, { 0x32, 0x00 } }, // 2
	{ { 3, 0, MOD_NONE  }, { 0x33, 0x00 } }, // 3
	{ { 3, 1, MOD_NONE  }, { 0x34, 0x00 } }, // 4
	{ { 4, 0, MOD_NONE  }, { 0x35, 0x00 } }, // 5
	{ { 4, 1, MOD_NONE  }, { 0x36, 0x00 } }, // 6
	{ { 5, 0, MOD_NONE  }, { 0x37, 0x00 } }, // 7
	{ { 5, 1, MOD_NONE  }, { 0x38, 0x00 } }, // 8
	{ { 6, 0, MOD_NONE  }, { 0x39, 0x00 } }, // 9
	{ { 5, 6, MOD_SHIFT }, { 0x3A, 0x00 } }, // :
	{ { 4, 7, MOD_SHIFT }, { 0x3B, 0x00 } }, // ;
	{ { 6, 1, MOD_SHIFT }, { 0x3D, 0x00 } }, // =
	{ { 9, 9, MOD_CODE  }, { 0x3E, 0x00 } }, // >
	{ { 6, 6, MOD_SHIFT }, { 0x3F, 0x00 } }, // ?
	{ { 1, 4, MOD_SHIFT }, { 0x41, 0x00 } }, // A
	{ { 3, 6, MOD_SHIFT }, { 0x42, 0x00 } }, // B
	{ { 2, 6, MOD_SHIFT }, { 0x43, 0x00 } }, // C
	{ { 2, 4, MOD_SHIFT }, { 0x44, 0x00 } }, // D
	{ { 2, 2, MOD_SHIFT }, { 0x45, 0x00 } }, // E
	{ { 2, 5, MOD_SHIFT }, { 0x46, 0x00 } }, // F
	{ { 3, 4, MOD_SHIFT }, { 0x47, 0x00 } }, // G
	{ { 3, 5, MOD_SHIFT }, { 0x48, 0x00 } }, // H
	{ { 5, 3, MOD_SHIFT }, { 0x49, 0x00 } }, // I
	{ { 4, 4, MOD_SHIFT }, { 0x4A, 0x00 } }, // J
	{ { 4, 5, MOD_SHIFT }, { 0x4B, 0x00 } }, // K
	{ { 5, 4, MOD_SHIFT }, { 0x4C, 0x00 } }, // L
	{ { 4, 6, MOD_SHIFT }, { 0x4D, 0x00 } }, // M
	{ { 3, 7, MOD_SHIFT }, { 0x4E, 0x00 } }, // N
	{ { 5, 2, MOD_SHIFT }, { 0x4F, 0x00 } }, // O
	{ { 6, 3, MOD_SHIFT }, { 0x50, 0x00 } }, // P
	{ { 1, 2, MOD_SHIFT }, { 0x51, 0x00 } }, // Q
	{ { 3, 3, MOD_SHIFT }, { 0x52, 0x00 } }, // R
	{ { 1, 5, MOD_SHIFT }, { 0x53, 0x00 } }, // S
	{ { 3, 2, MOD_SHIFT }, { 0x54, 0x00 } }, // T
	{ { 4, 2, MOD_SHIFT }, { 0x55, 0x00 } }, // U
	{ { 2, 7, MOD_SHIFT }, { 0x56, 0x00 } }, // V
	{ { 2, 3, MOD_SHIFT }, { 0x57, 0x00 } }, // W
	{ { 1, 7, MOD_SHIFT }, { 0x58, 0x00 } }, // X
	{ { 1, 6, MOD_SHIFT }, { 0x59, 0x00 } }, // Y
	{ { 4, 3, MOD_SHIFT }, { 0x5A, 0x00 } }, // Z
	{ { 5, 7, MOD_SHIFT }, { 0x5F, 0x00 } }, // _
	{ { 7, 1, MOD_SHIFT }, { 0x60, 0x00 } }, // `
	{ { 1, 4, MOD_NONE  }, { 0x61, 0x00 } }, // a
	{ { 3, 6, MOD_NONE  }, { 0x62, 0x00 } }, // b
	{ { 2, 6, MOD_NONE  }, { 0x63, 0x00 } }, // c
	{ { 2, 4, MOD_NONE  }, { 0x64, 0x00 } }, // d
	{ { 2, 2, MOD_NONE  }, { 0x65, 0x00 } }, // e
	{ { 2, 5, MOD_NONE  }, { 0x66, 0x00 } }, // f
	{ { 3, 4, MOD_NONE  }, { 0x67, 0x00 } }, // g
	{ { 3, 5, MOD_NONE  }, { 0x68, 0x00 } }, // h
	{ { 5, 3, MOD_NONE  }, { 0x69, 0x00 } }, // i
	{ { 4, 4, MOD_NONE  }, { 0x6A, 0x00 } }, // j
	{ { 4, 5, MOD_NONE  }, { 0x6B, 0x00 } }, // k
	{ { 5, 4, MOD_NONE  }, { 0x6C, 0x00 } }, // l
	{ { 4, 6, MOD_NONE  }, { 0x6D, 0x00 } }, // m
	{ { 3, 7, MOD_NONE  }, { 0x6E, 0x00 } }, // n
	{ { 5, 2, MOD_NONE  }, { 0x6F, 0x00 } }, // o
	{ { 6, 3, MOD_NONE  }, { 0x70, 0x00 } }, // p
	{ { 1, 2, MOD_NONE  }, { 0x71, 0x00 } }, // q
	{ { 3, 3, MOD_NONE  }, { 0x72, 0x00 } }, // r
	{ { 1, 5, MOD_NONE  }, { 0x73, 0x00 } }, // s
	{ { 3, 2, MOD_NONE  }, { 0x74, 0x00 } }, // t
	{ { 4, 2, MOD_NONE  }, { 0x75, 0x00 } }, // u
	{ { 2, 7, MOD_NONE  }, { 0x76, 0x00 } }, // v
	{ { 2, 3, MOD_NONE  }, { 0x77, 0x00 } }, // w
	{ { 1, 7, MOD_NONE  }, { 0x78, 0x00 } }, // x
	{ { 1, 6, MOD_NONE  }, { 0x79, 0x00 } }, // y
	{ { 4, 3, MOD_NONE  }, { 0x7A, 0x00 } }, // z

	{ { 3, 0, MOD_SHIFT }, { 0x99, 0x00 } }, // §
	{ { 7, 1, MOD_NONE  }, { 0x9A, 0x00 } }, // ´
	{ { 4, 2, MOD_CODE  }, { 0x9B, 0x00 } }, // µ
	{ { 1, 7, MOD_CODE  }, { 0x9C, 0x00 } }, // ²
	{ { 2, 7, MOD_CODE  }, { 0x9D, 0x00 } }, // ³
	{ { 2, 3, MOD_CODE  }, { 0x9E, 0x00 } }, // °
	{ { 6, 4, MOD_NONE  }, { 0x9F, 0x00 } }, // ä
	{ { 6, 4, MOD_SHIFT }, { 0xA0, 0x00 } }, // Ä
	{ { 5, 5, MOD_NONE  }, { 0xA1, 0x00 } }, // ö
	{ { 5, 5, MOD_SHIFT }, { 0xA2, 0x00 } }, // Ö
	{ { 6, 2, MOD_NONE  }, { 0xA3, 0x00 } }, // ü
	{ { 6, 2, MOD_SHIFT }, { 0xA4, 0x00 } }, // Ü
	{ { 6, 6, MOD_NONE  }, { 0xA5, 0x00 } }, // ß

	{ { 7, 4, MOD_NONE  }, { 0x0A, 0x00 } }, // CRLF // !!!!!!!!!!!!!!TEMP!!!!!!!!!!!!!!!! actual line: { { 7, 4, MOD_NONE  }, { 0x80, 0x80 } },
	{ { 0, 7, MOD_NONE  }, { 0x00, 0x81 } }, // WORD OUT

	{ { 0, 0, MOD_NONE  }, { 0x00, 0x83 } }, // Pitch
	{ { 0, 1, MOD_NONE  }, { 0x00, 0x84 } }, // Line
	{ { 0, 2, MOD_NONE  }, { 0x00, 0x85 } }, // LMAR
	{ { 0, 2, MOD_CODE  }, { 0x00, 0x86 } }, // RMAR
	{ { 0, 4, MOD_NONE  }, { 0x00, 0x88 } }, // T+
	{ { 0, 4, MOD_CODE  }, { 0x00, 0x89 } }, // T-
	{ { 0, 5, MOD_NONE  }, { 0x00, 0x8A } }, // Caps Lock
	{ { 0, 7, MOD_CODE  }, { 0x00, 0x8B } }, // LINE OUT
	{ { 1, 1, MOD_CODE  }, { 0x00, 0x8C } }, // L IND Top
	{ { 1, 3, MOD_CODE  }, { 0x00, 0x8D } }, // L IND Bot
	{ { 1, 1, MOD_NONE  }, { 0x00, 0x8E } }, // Return L Top
	{ { 1, 3, MOD_NONE  }, { 0x00, 0x8F } }, // Return L Bot
	{ { 6, 7, MOD_CODE  }, { 0x00, 0x90 } }, // Backspace
	{ { 7, 0, MOD_NONE  }, { 0x00, 0x91 } }, // <-||->
	{ { 7, 2, MOD_NONE  }, { 0x00, 0x92 } }, // RELOC
	{ { 7, 2, MOD_CODE  }, { 0x00, 0x93 } }, // |-<-|
	{ { 7, 5, MOD_NONE  }, { 0x00, 0x94 } }, // |<-|
	{ { 7, 5, MOD_CODE  }, { 0x00, 0x95 } }, // <<-
	{ { 7, 6, MOD_NONE  }, { 0x00, 0x96 } }, // INDEX
	{ { 7, 6, MOD_CODE  }, { 0x00, 0x97 } }, // REV
};

#endif // __KEYBOARD_HPP
