#include "Keyboard.hpp"

#include <wiringPi.h>

bool Keyboard::initialized = false;

void Keyboard::setupPins() {
    if (this->initialized) return;

    wiringPiSetupGpio();

    for (const auto& pin : pinsScan) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }

    for (const auto& pin : pinsOut) {
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP);
    }

    this->initialized = true;
}

Keyboard::Keyboard(const std::vector<int>& pinsScan, const std::vector<int>& pinsOut) {
    this->pinsScan = pinsScan;
    this->pinsOut = pinsOut;

    this->setupPins();
}

KeymapEntry Keyboard::readKey() {
    for (int iscan = 0; iscan < this->pinsScan.size(); iscan++) {
        digitalWrite(this->pinsScan[iscan], LOW);
        delay(1);
        for (int iout = 0; iout < this->pinsOut.size(); iout++) {
            KeymapKey mapKey = { iscan, iout, MOD_NONE };

            // skip mod keys
            if (modkeymap.contains(mapKey)) continue;

            if (digitalRead(this->pinsOut[iout]) == LOW) {
                // check mod keys
                digitalWrite(this->pinsScan[iscan], HIGH);

                for (const auto& kv : modkeymap) {
                    if (kv.second == MOD_NONE) continue;
                    digitalWrite(this->pinsScan[iscan], LOW);
                    delay(1);
                    if (digitalRead(this->pinsOut[kv.first.scan]) == LOW) mapKey.mod |= kv.second;
                    digitalWrite(this->pinsScan[kv.first.scan], HIGH);
                }

                if (keymap.contains(mapKey))
                    return keymap.at(mapKey);
            }
        }
        digitalWrite(this->pinsScan[iscan], HIGH);
    }
    return { 0x00, 0x00 };
}
