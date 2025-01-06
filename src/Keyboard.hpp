#ifndef __KEYBOARD_HPP
#define __KEYBOARD_HPP

#include <Arduino.h>
#include <Keymap.hpp>

extern uint8_t scanPorts[9];
extern uint8_t outPorts[8];

void waitForEdge(uint8_t scan, uint8_t state) {
  uint8_t targetState = state == RISING ? LOW : HIGH;
  while (digitalRead(scanPorts[scan]) == targetState);
}

void writeKey(size_t keycode) {
  KeymapEntry key = keymap[keycode - 0x20];
  for (int i = 0; i < 2; i++) {
    waitForEdge(key.scan, FALLING);
    digitalWrite(outPorts[key.out], LOW);
    waitForEdge(key.scan, RISING);
    digitalWrite(outPorts[key.out], HIGH);
  }
  waitForEdge(key.scan, FALLING);
  for (int i = 0; i < 3; i++) {
    waitForEdge(key.scan, RISING);
    waitForEdge(key.scan, FALLING);
  }
}

#endif // __KEYBOARD_HPP