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

#define KEY_RETURN 0x3C // ASCII '<'

// index = char - 0x20
extern KeymapEntry keymap[91];

#endif // __KEYMAP_HPP
