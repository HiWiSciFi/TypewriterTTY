#include <cstdint>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include <wiringPi.h>

#include "Keymap.hpp"
#include "PseudoTTY.hpp"

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
    for (int m = 0; m < (sizeof(pinsScan) / sizeof(*pinsScan)); m++) {
        digitalWrite(pinsScan[m], LOW);
        delay(1);
        for (int i = 0; i < (sizeof(pinsOut) / sizeof(*pinsOut)); i++) {
            KeymapKey mapKey = { m, i, MOD_NONE };

            // skip mod keys
            if (modkeymap.contains(mapKey)) continue;

            if (digitalRead(pinsOut[i]) == LOW) {
                // check mod keys
                digitalWrite(pinsScan[m], HIGH);

                for (auto& kv : modkeymap) {
                    if (kv.second == MOD_NONE) continue;
                    digitalWrite(pinsScan[kv.first.scan], LOW);
                    delay(1);
                    if (digitalRead(pinsOut[kv.first.out]) == LOW) mapKey.mod |= kv.second;
                    digitalWrite(pinsScan[kv.first.scan], HIGH);
                }

                if (keymap.contains(mapKey))
                    return keymap.at(mapKey);
            }
        }
        digitalWrite(pinsScan[m], HIGH);
    }
    return { 0x00, 0x00 };
}

void setupPins() {
    wiringPiSetupGpio();

    for (int i = 0; i < (sizeof(pinsScan) / sizeof(*pinsScan)); i++) {
        pinMode(pinsScan[i], OUTPUT);
        digitalWrite(pinsScan[i], HIGH);
    }

    for (int i = 0; i < (sizeof(pinsOut) / sizeof(*pinsOut)); i++) {
        pinMode(pinsOut[i], INPUT);
        pullUpDnControl(pinsOut[i], PUD_UP);
    }
}

int main(int argc, char** argv) {
    PseudoTTY pty(200, 1, { "/bin/bash" });
    pty.openTTY();
    sleep(1); // give bash time to start up

    setupPins();

    KeymapEntry lastKey = { 0x00, 0x00 };
    while (true) {
        std::string ptyContent = pty.readTTY();
        std::cout << ptyContent << std::flush;

        KeymapEntry key = readKey();

        // not if same key
        if (key == lastKey) continue;
        lastKey = key;
        // not if no key
        if (key == KeymapEntry{ 0x00, 0x00 }) continue;

        // std::cout << static_cast<char>(key.codepoint) << std::flush;
        pty.writeTTY(static_cast<char>(key.codepoint));
    }
}
