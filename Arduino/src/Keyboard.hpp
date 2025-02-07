#ifndef __KEYBOARD_HPP
#define __KEYBOARD_HPP

#include "Keymap.hpp"

// returns 0 on success, -1 on error
int writeKey(uint8_t keycode);

#endif // __KEYBOARD_HPP
