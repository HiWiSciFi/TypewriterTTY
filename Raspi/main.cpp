#include <cstdint>
#include <iomanip>
#include <iostream>

uint32_t readCodepoint() {
    int c = fgetc(stdin);
    if (c == EOF) {
        // TODO: error
    }

    uint8_t size = 0;
    if ((c & 0b1000'0000) == 0b0000'0000)
        size = 0;
    else if ((c & 0b1110'0000) == 0b1100'0000)
        size = 1;
    else if ((c & 0b1111'0000) == 0b1110'0000)
        size = 2;
    else if ((c & 0b1111'1000) == 0b1111'0000)
        size = 3;
    else {
        // TODO: error
    }

    static uint8_t masks[] = { 0b0111'1111, 0b0001'1111, 0b0000'1111, 0b0000'0111 };
    uint8_t mask = masks[size];

    uint32_t codepoint = (c & mask) << (size * 6);

    for (int8_t off = size - 1; off >= 0; off--) {
        c = fgetc(stdin);
        if (c == EOF || (c & 0b1100'0000) != 0b1000'0000) {
            // TODO: error
        }
        codepoint |= c << (off * 6);
    }

    return codepoint;
}

int main(int argc, char** argv) {
    while (true) {
        uint32_t codepoint = readCodepoint();
        std::cout << "U+" << std::setfill('0') << std::setw(6) << std::right << std::hex << codepoint << std::endl;
    }
}
