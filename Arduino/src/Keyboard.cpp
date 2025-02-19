#include "Keyboard.hpp"

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

int writeKey(uint8_t keycode) {
	if (keycode > (sizeof( keymap ) / sizeof( keymap[0] ))) return -1;
	KeymapEntry key = keymap[keycode];
	if (!key.valid) return -1;

	if (key.mod & MOD_SHFT) outputKey(8, 6);
	if (key.mod & MOD_CODE) outputKey(0, 3);

	for (int i = 0; i < 4; i++) {
		outputKey(key.scan, key.out);
		if (key.mod & MOD_SHFT) outputKey(8, 6);
		if (key.mod & MOD_CODE) outputKey(0, 3);
	}

	delay(100); // wait 100 ms for printing
	if (keycode == 0x0a) { // LF
		delay(2500); // wait for carriage to return
	}

	return 0;
}

void waitForScan(uint8_t scan) {
	waitForEdge(scan, RISING);
}
