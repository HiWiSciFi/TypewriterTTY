#include <Keyboard.hpp>

#include <Arduino.h>

extern uint8_t scanPorts[9];
extern uint8_t outPorts[8];

static void waitForEdge(uint8_t scan, uint8_t state) {
	uint8_t targetState = state == RISING ? LOW : HIGH;
	while (digitalRead(scanPorts[scan]) == targetState);
}

static void outputKey(uint8_t scan, uint8_t out) {
	waitForEdge(scan, FALLING);
	digitalWrite(outPorts[out], LOW);
	waitForEdge(scan, RISING);
	digitalWrite(outPorts[out], HIGH);
}

void writeKey(uint16_t keycode) {
	KeymapEntry key = keymap[keycode];

	if (key.mod & MOD_SHIFT) outputKey(8, 6);
	if (key.mod & MOD_CODE) outputKey(0, 3);

	for (int i = 0; i < 3; i++) {
		outputKey(key.scan, key.out);
		if (key.mod & MOD_SHIFT) outputKey(8, 6);
		if (key.mod & MOD_CODE) outputKey(0, 3);
	}

	waitForEdge(key.scan, FALLING);
	for (int i = 0; i < 3; i++) {
		waitForEdge(key.scan, RISING);
		waitForEdge(key.scan, FALLING);
	}
}
