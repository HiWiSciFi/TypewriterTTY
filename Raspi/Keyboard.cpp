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

#include <iostream>
KeymapEntry Keyboard::readKey() {
	for (int iscan = 0; iscan < this->pinsScan.size(); iscan++) {
		digitalWrite(this->pinsScan[iscan], LOW);
		timespec ts = { .tv_sec = 0, .tv_nsec = 1000 };
		nanosleep(&ts, &ts);
		for (int iout = 0; iout < this->pinsOut.size(); iout++) {
			KeymapKey mapKey = { iscan, iout, MOD_NONE };

			// skip mod keys
			if (modkeymap.contains(mapKey)) continue;

			if (digitalRead(this->pinsOut[iout]) == LOW) {
				// check mod keys
				digitalWrite(this->pinsScan[iscan], HIGH);

				for (const auto& kv : modkeymap) {
					if (kv.second == MOD_NONE) continue;
					digitalWrite(this->pinsScan[kv.first.scan], LOW);
					ts = { .tv_sec = 0, .tv_nsec = 1000 };
					nanosleep(&ts, &ts);
					if (digitalRead(this->pinsOut[kv.first.out]) == LOW) {
						mapKey.mod |= kv.second;
					}
					digitalWrite(this->pinsScan[kv.first.scan], HIGH);
				}

				// std::cout << "READ: KEY " << mapKey.scan << " " << mapKey.out << " " << static_cast<int>(mapKey.mod) << std::endl;
				if (keymap.contains(mapKey)) {
					return keymap.at(mapKey);
				} else {
					std::cout << "Key not found: " << iscan << ":" << iout << std::endl;
				}
			}
		}
		digitalWrite(this->pinsScan[iscan], HIGH);
	}
	return { 0x00, 0x00 };
}
