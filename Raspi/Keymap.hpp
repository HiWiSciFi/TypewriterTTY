#ifndef __KEYMAP_HPP
#define __KEYMAP_HPP

#include <cstdint>
#include <map>

#define MOD_NONE  0x00
#define MOD_SHIFT 0x01
#define MOD_CODE  0x02

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

static std::map<KeymapKey, uint8_t> modkeymap = {
    { { 8, 6, MOD_NONE }, MOD_SHIFT }, // SHIFT L R
    { { 0, 3, MOD_NONE }, MOD_CODE  }, // CODE
    { { 1, 0, MOD_NONE }, MOD_NONE  }, // Case Open
};

static std::map<KeymapKey, KeymapEntry> keymap = {
    { { 6, 7, MOD_NONE  }, { 0x08, 0x08 } }, // Backspace

    { { 7, 7, MOD_NONE  }, { 0x20, 0x20 } }, // SPACE
    { { 2, 0, MOD_SHIFT }, { 0x21, 0x21 } }, // !
    { { 2, 1, MOD_SHIFT }, { 0x22, 0x22 } }, // "
    { { 6, 5, MOD_NONE  }, { 0x23, 0x23 } }, // #
    { { 3, 1, MOD_SHIFT }, { 0x24, 0x24 } }, // $
    { { 4, 0, MOD_SHIFT }, { 0x25, 0x25 } }, // %
    { { 4, 1, MOD_SHIFT }, { 0x26, 0x26 } }, // &
    { { 6, 5, MOD_SHIFT }, { 0x27, 0x27 } }, // '
    { { 5, 1, MOD_SHIFT }, { 0x28, 0x28 } }, // (
    { { 6, 0, MOD_SHIFT }, { 0x29, 0x29 } }, // )
    { { 7, 3, MOD_SHIFT }, { 0x2A, 0x2A } }, // *
    { { 7, 3, MOD_NONE  }, { 0x2B, 0x2B } }, // +
    { { 4, 7, MOD_NONE  }, { 0x2C, 0x2C } }, // ,
    { { 5, 7, MOD_NONE  }, { 0x2D, 0x2D } }, // -
    { { 5, 6, MOD_NONE  }, { 0x2E, 0x2E } }, // .
    { { 5, 0, MOD_SHIFT }, { 0x2F, 0x2F } }, // /
    { { 6, 1, MOD_NONE  }, { 0x30, 0x30 } }, // 0
    { { 2, 0, MOD_NONE  }, { 0x31, 0x31 } }, // 1
    { { 2, 1, MOD_NONE  }, { 0x32, 0x32 } }, // 2
    { { 3, 0, MOD_NONE  }, { 0x33, 0x33 } }, // 3
    { { 3, 1, MOD_NONE  }, { 0x34, 0x34 } }, // 4
    { { 4, 0, MOD_NONE  }, { 0x35, 0x35 } }, // 5
    { { 4, 1, MOD_NONE  }, { 0x36, 0x36 } }, // 6
    { { 5, 0, MOD_NONE  }, { 0x37, 0x37 } }, // 7
    { { 5, 1, MOD_NONE  }, { 0x38, 0x38 } }, // 8
    { { 6, 0, MOD_NONE  }, { 0x39, 0x39 } }, // 9
    { { 5, 6, MOD_SHIFT }, { 0x3A, 0x3A } }, // :
    { { 4, 7, MOD_SHIFT }, { 0x3B, 0x3B } }, // ;
    { { 6, 1, MOD_SHIFT }, { 0x3D, 0x3D } }, // =
    { { 9, 9, MOD_CODE  }, { 0x3E, 0x3E } }, // >
    { { 6, 6, MOD_SHIFT }, { 0x3F, 0x3F } }, // ?
    { { 1, 4, MOD_SHIFT }, { 0x41, 0x41 } }, // A
    { { 3, 6, MOD_SHIFT }, { 0x42, 0x42 } }, // B
    { { 2, 6, MOD_SHIFT }, { 0x43, 0x43 } }, // C
    { { 2, 4, MOD_SHIFT }, { 0x44, 0x44 } }, // D
    { { 2, 2, MOD_SHIFT }, { 0x45, 0x45 } }, // E
    { { 2, 5, MOD_SHIFT }, { 0x46, 0x46 } }, // F
    { { 3, 4, MOD_SHIFT }, { 0x47, 0x47 } }, // G
    { { 3, 5, MOD_SHIFT }, { 0x48, 0x48 } }, // H
    { { 5, 3, MOD_SHIFT }, { 0x49, 0x49 } }, // I
    { { 4, 4, MOD_SHIFT }, { 0x4A, 0x4A } }, // J
    { { 4, 5, MOD_SHIFT }, { 0x4B, 0x4B } }, // K
    { { 5, 4, MOD_SHIFT }, { 0x4C, 0x4C } }, // L
    { { 4, 6, MOD_SHIFT }, { 0x4D, 0x4D } }, // M
    { { 3, 7, MOD_SHIFT }, { 0x4E, 0x4E } }, // N
    { { 5, 2, MOD_SHIFT }, { 0x4F, 0x4F } }, // O
    { { 6, 3, MOD_SHIFT }, { 0x50, 0x50 } }, // P
    { { 1, 2, MOD_SHIFT }, { 0x51, 0x51 } }, // Q
    { { 3, 3, MOD_SHIFT }, { 0x52, 0x52 } }, // R
    { { 1, 5, MOD_SHIFT }, { 0x53, 0x53 } }, // S
    { { 3, 2, MOD_SHIFT }, { 0x54, 0x54 } }, // T
    { { 4, 2, MOD_SHIFT }, { 0x55, 0x55 } }, // U
    { { 2, 7, MOD_SHIFT }, { 0x56, 0x56 } }, // V
    { { 2, 3, MOD_SHIFT }, { 0x57, 0x57 } }, // W
    { { 1, 7, MOD_SHIFT }, { 0x58, 0x58 } }, // X
    { { 1, 6, MOD_SHIFT }, { 0x59, 0x59 } }, // Y
    { { 4, 3, MOD_SHIFT }, { 0x5A, 0x5A } }, // Z
    { { 5, 7, MOD_SHIFT }, { 0x5F, 0x5F } }, // _
    { { 7, 1, MOD_SHIFT }, { 0x60, 0x60 } }, // `
    { { 1, 4, MOD_NONE  }, { 0x61, 0x61 } }, // a
    { { 3, 6, MOD_NONE  }, { 0x62, 0x62 } }, // b
    { { 2, 6, MOD_NONE  }, { 0x63, 0x63 } }, // c
    { { 2, 4, MOD_NONE  }, { 0x64, 0x64 } }, // d
    { { 2, 2, MOD_NONE  }, { 0x65, 0x65 } }, // e
    { { 2, 5, MOD_NONE  }, { 0x66, 0x66 } }, // f
    { { 3, 4, MOD_NONE  }, { 0x67, 0x67 } }, // g
    { { 3, 5, MOD_NONE  }, { 0x68, 0x68 } }, // h
    { { 5, 3, MOD_NONE  }, { 0x69, 0x69 } }, // i
    { { 4, 4, MOD_NONE  }, { 0x6A, 0x6A } }, // j
    { { 4, 5, MOD_NONE  }, { 0x6B, 0x6B } }, // k
    { { 5, 4, MOD_NONE  }, { 0x6C, 0x6C } }, // l
    { { 4, 6, MOD_NONE  }, { 0x6D, 0x6D } }, // m
    { { 3, 7, MOD_NONE  }, { 0x6E, 0x6E } }, // n
    { { 5, 2, MOD_NONE  }, { 0x6F, 0x6F } }, // o
    { { 6, 3, MOD_NONE  }, { 0x70, 0x70 } }, // p
    { { 1, 2, MOD_NONE  }, { 0x71, 0x71 } }, // q
    { { 3, 3, MOD_NONE  }, { 0x72, 0x72 } }, // r
    { { 1, 5, MOD_NONE  }, { 0x73, 0x73 } }, // s
    { { 3, 2, MOD_NONE  }, { 0x74, 0x74 } }, // t
    { { 4, 2, MOD_NONE  }, { 0x75, 0x75 } }, // u
    { { 2, 7, MOD_NONE  }, { 0x76, 0x76 } }, // v
    { { 2, 3, MOD_NONE  }, { 0x77, 0x77 } }, // w
    { { 1, 7, MOD_NONE  }, { 0x78, 0x78 } }, // x
    { { 1, 6, MOD_NONE  }, { 0x79, 0x79 } }, // y
    { { 4, 3, MOD_NONE  }, { 0x7A, 0x7A } }, // z

    { { 7, 4, MOD_NONE  }, { 0x0A, 0x0A } }, // CRLF // !!!!!!!!!!!!!!TEMP!!!!!!!!!!!!!!!! actual line: { { 7, 4, MOD_NONE  }, { 0x80, 0x80 } },
    { { 0, 7, MOD_NONE  }, { 0x81, 0x81 } }, // WORD OUT

    { { 0, 0, MOD_NONE  }, { 0x83, 0x83 } }, // Pitch
    { { 0, 1, MOD_NONE  }, { 0x84, 0x84 } }, // Line
    { { 0, 2, MOD_NONE  }, { 0x85, 0x85 } }, // LMAR
    { { 0, 2, MOD_CODE  }, { 0x86, 0x86 } }, // RMAR
    { { 0, 4, MOD_NONE  }, { 0x88, 0x88 } }, // T+
    { { 0, 4, MOD_CODE  }, { 0x89, 0x89 } }, // T-
    { { 0, 5, MOD_NONE  }, { 0x8A, 0x8A } }, // Caps Lock
    { { 0, 7, MOD_CODE  }, { 0x8B, 0x8B } }, // LINE OUT
    { { 1, 1, MOD_CODE  }, { 0x8C, 0x8C } }, // L IND Top
    { { 1, 3, MOD_CODE  }, { 0x8D, 0x8D } }, // L IND Bot
    { { 1, 1, MOD_NONE  }, { 0x8E, 0x8E } }, // Return L Top
    { { 1, 3, MOD_NONE  }, { 0x8F, 0x8F } }, // Return L Bot
    { { 6, 7, MOD_CODE  }, { 0x90, 0x90 } }, // Backspace
    { { 7, 0, MOD_NONE  }, { 0x91, 0x91 } }, // <-||->
    { { 7, 2, MOD_NONE  }, { 0x92, 0x92 } }, // RELOC
    { { 7, 2, MOD_CODE  }, { 0x93, 0x93 } }, // |-<-|
    { { 7, 5, MOD_NONE  }, { 0x94, 0x94 } }, // |<-|
    { { 7, 5, MOD_CODE  }, { 0x95, 0x95 } }, // <<-
    { { 7, 6, MOD_NONE  }, { 0x96, 0x96 } }, // INDEX
    { { 7, 6, MOD_CODE  }, { 0x97, 0x97 } }, // REV

    { { 3, 0, MOD_SHIFT }, { 0x99, 0x99 } }, // §
    { { 7, 1, MOD_NONE  }, { 0x9A, 0x9A } }, // ´
    { { 4, 2, MOD_CODE  }, { 0x9B, 0x9B } }, // µ
    { { 1, 7, MOD_CODE  }, { 0x9C, 0x9C } }, // ²
    { { 2, 7, MOD_CODE  }, { 0x9D, 0x9D } }, // ³
    { { 2, 3, MOD_CODE  }, { 0x9E, 0x9E } }, // °
    { { 6, 4, MOD_NONE  }, { 0x9F, 0x9F } }, // ä
    { { 6, 4, MOD_SHIFT }, { 0xA0, 0xA0 } }, // Ä
    { { 5, 5, MOD_NONE  }, { 0xA1, 0xA1 } }, // ö
    { { 5, 5, MOD_SHIFT }, { 0xA2, 0xA2 } }, // Ö
    { { 6, 2, MOD_NONE  }, { 0xA3, 0xA3 } }, // ü
    { { 6, 2, MOD_SHIFT }, { 0xA4, 0xA4 } }, // Ü
    { { 6, 6, MOD_NONE  }, { 0xA5, 0xA5 } }, // ß
};

#endif // __KEYMAP_HPP
