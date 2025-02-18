#include "Keyboard.hpp"

#include <wiringPi.h>

#include "Util.hpp"

Keyboard::Keyboard(const std::shared_ptr<KeyboardConfig>& config) {
	this->config = config;
}

void Keyboard::Setup() {
	wiringPiSetupGpio();

	for (const auto& pin : this->config->pinsScan) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}

	for (const auto& pin : this->config->pinsOut) {
		pinMode(pin, INPUT);
		pullUpDnControl(pin, PUD_UP);
	}
}

#include <iostream>
Keyboard::KeyResult Keyboard::GetKey() {
	KeyResult result = { KeyType::NONE, 0x00000000, 0x00 };

	bool found = false;
	for (int iscan = 0; iscan < this->config->pinsScan.size(); iscan++) {
		digitalWrite(this->config->pinsScan[iscan], LOW);

		// TODO: sleep
		// TODO: check necessity
		// Util::Sleep(0, 1, 0);
		timespec ts = { .tv_sec = 0, .tv_nsec = 1000000 * 1 };
		nanosleep(&ts, &ts);

		for (int iout = 0; iout < this->config->pinsOut.size(); iout++) {
			KeyboardConfig::KeyboardKey mapKey = { { iscan, iout }, MOD_NONE };

			// skip mod keys
			if (this->config->modMap.contains(mapKey.pos)) continue;

			if (digitalRead(this->config->pinsOut[iout]) == LOW) {
				// check mod keys
				digitalWrite(this->config->pinsScan[iscan], HIGH);

				for (const auto& modkey : this->config->modMap) {
					if (modkey.second == MOD_NONE) continue;

					digitalWrite(this->config->pinsScan[modkey.first.scan], LOW);

					// TODO: sleep
					// TODO: check necessity
					// Util::Sleep(0, 1, 0);
					ts = { .tv_sec = 0, .tv_nsec = 1000000 * 1 };
					nanosleep(&ts, &ts);

					if (digitalRead(this->config->pinsOut[modkey.first.out]) == LOW) {
						mapKey.mod |= modkey.second;
					}
					digitalWrite(this->config->pinsScan[modkey.first.scan], HIGH);
				}
				digitalWrite(this->config->pinsScan[iscan], HIGH);

				if (this->config->codepointMap.contains(mapKey)) {
					// codepoint
					result.type = KeyType::UNICODE;
					result.codepoint = this->config->codepointMap.at(mapKey);
					found = true;
					break;
				}
				else if (this->config->keyMap.contains(mapKey)) {
					// keycode
					result.type = KeyType::KEYCODE;
					result.keycode = this->config->keyMap.at(mapKey);
					found = true;
					break;
				}
				else {
					std::cout << "Key not found" << std::endl;
				}
			}
		}
		digitalWrite(this->config->pinsScan[iscan], HIGH);
		if (found) break;
	}

	return result;
}
