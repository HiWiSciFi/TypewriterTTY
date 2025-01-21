#include <cstdint>
#include <iomanip>
#include <iostream>

#include <wiringPi.h>

#include "Keymap.hpp"

// +-----+-----+---------+------+---+Pi Zero 2W+---+------+---------+-----+-----+
// | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
// +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
// |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
// |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
// |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
// |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 0 | IN   | TxD     | 15  | 14  |
// |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
// |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
// |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
// |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
// |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
// |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
// |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
// |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
// |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
// |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
// |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
// |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
// |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
// |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
// |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
// |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
// +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
// | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
// +-----+-----+---------+------+---+Pi Zero 2W+---+------+---------+-----+-----+

int pinsScan[] = { 2, 3, 4, 17, 27, 22, 10, 9, 11 };
int pinsOut[] = { 18, 23, 24, 25, 8, 7, 12, 16 };

uint32_t readCodepoint() {
    int c = fgetc(stdin);
    if (c == EOF) {
        // TODO: fgetc error
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
        // TODO: error, unexpected byte
    }

    static uint8_t masks[] = { 0b0111'1111, 0b0001'1111, 0b0000'1111, 0b0000'0111 };
    uint8_t mask = masks[size];

    uint32_t codepoint = (c & mask) << (size * 6);

    for (int8_t off = size - 1; off >= 0; off--) {
        c = fgetc(stdin);
        if (c == EOF) {
            // TODO: fgetc error
        }

        if ((c & 0b1100'0000) != 0b1000'0000) {
            // TODO: error, unexpected byte
        }

        codepoint |= c << (off * 6);
    }

    return codepoint;
}

KeymapEntry readKey() {
    KeymapKey key = { -1, -1, MOD_NONE };
    // scan lines
    for (uint8_t scan = 0; scan < sizeof(pinsScan) / sizeof(*pinsScan); scan++) {
        digitalWrite(pinsScan[scan], LOW);
        delay(1);
        for (uint8_t out = 0; out < sizeof(pinsOut) / sizeof(*pinsOut); out++) {
            // TODO: skip shift and code keys

            int status = digitalRead(pinsOut[out]);
            if (status == LOW) {
                key = { scan, out, MOD_NONE };
                break;
            }
        }
        digitalWrite(pinsScan[scan], HIGH);

        if (key.scan != -1) break;
    }

    // TODO: Read mod key

    if (key.scan == -1 || keymap.count(key) == 0) return { 0, 0 };
    std::cout << "Key test " << key.scan << " " << key.out << std::endl;
    return keymap.at(key);
}

#define PIN_SCAN 3

int main(int argc, char** argv) {
    wiringPiSetupGpio();

    pinMode(PIN_SCAN, OUTPUT);

    for (int i = 0; i < (sizeof(pinsOut) / sizeof(*pinsOut)); i++) {
        pinMode(pinsOut[i], INPUT);
        pullUpDnControl(pinsOut[i], PUD_UP);
    }

    digitalWrite(PIN_SCAN, LOW);

    while (true) {
        for (int i = 1; i < (sizeof(pinsOut) / sizeof(*pinsOut)); i++) {
            if (digitalRead(pinsOut[i]) == LOW) {
                std::cout << i << " pressed" << std::endl;
            }
        }
    }

    // for (uint8_t i = 0; i < sizeof(pinsScan) / sizeof(*pinsScan); i++) {
    //     pinMode(pinsScan[i], OUTPUT);
    //     digitalWrite(pinsScan[i], HIGH);
    // }
    // for (uint8_t i = 0; i < sizeof(pinsOut) / sizeof(*pinsOut); i++) {
    //     pinMode(pinsOut[i], INPUT);
    //     pullUpDnControl(pinsOut[i], PUD_UP);
    // }

    // while (true) {
    //     auto key = readKey();
    //     if (key.codepoint == 0 && key.key == 0)
    //         continue;
    //     std::cout << "Key U+" << std::setfill('0') << std::setw(6) << std::right << std::hex << key.codepoint
    //               << " ASCII 0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << static_cast<int>(key.key) << std::endl;
    // }

    // while (true) {
    //     uint32_t codepoint = readCodepoint();
    //     std::cout << "U+" << std::setfill('0') << std::setw(6) << std::right << std::hex << codepoint << std::endl;
    // }
}
