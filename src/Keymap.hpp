#ifndef __KEYMAP_HPP
#define __KEYMAP_HPP

#include <inttypes.h>

struct KeymapEntry {
  uint8_t scan;
  uint8_t out;
  uint8_t mod;
};

#define MOD_NONE  0x00
#define MOD_SHIFT 0x01
#define MOD_CODE  0x02

#define KEY_RETURN    0x3C // ASCII '<' --> RET
#define KEY_MICRO     0x3E // ASCII '>' --> µ
#define KEY_BACKSPACE 0x40 // ASCII '@' --> BACK
#define KEY_DEL_WORD  0x5B // ASCII '[' --> WORD OUT

// index = char - 0x20
extern KeymapEntry keymap[91];

#endif // __KEYMAP_HPP
