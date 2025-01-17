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
};

struct KeymapKey {
    int scan;
    int out;
    uint8_t mod;

    bool operator<(const KeymapKey rhs) {
        return 
            (scan < rhs.scan)
            || (scan == rhs.scan && out < rhs.out)
            || (scan == rhs.scan && out == rhs.out && mod < rhs.mod);
    }
};

static std::map<KeymapKey, KeymapEntry> keymap = {
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
};

#endif // __KEYMAP_HPP
