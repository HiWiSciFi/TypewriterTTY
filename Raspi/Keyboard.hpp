#ifndef __KEYBOARD_HPP
#define __KEYBOARD_HPP

#include <vector>

#include "Keymap.hpp"

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

#endif // __KEYBOARD_HPP
