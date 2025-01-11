#include <Keyboard.hpp>

#include <Arduino.h>

extern uint8_t scanPorts[9];
extern uint8_t outPorts[8];

static void waitForEdge(uint8_t scan, uint8_t state) {
  uint8_t targetState = state == RISING ? LOW : HIGH;
  while (digitalRead(scanPorts[scan]) == targetState)
    ;
}

void writeKey(uint16_t keycode) {
  KeymapEntry key = keymap[keycode - 0x20];

  // Serial.print("Writing scan ");
  // Serial.print(key.scan);
  // Serial.print(" out ");
  // Serial.println(key.out);

  if (key.mod & MOD_SHIFT) {
    waitForEdge(8, FALLING);
    digitalWrite(outPorts[6], LOW);
    waitForEdge(8, RISING);
    digitalWrite(outPorts[6], HIGH);
  }

  if (key.mod & MOD_CODE) {
    waitForEdge(0, FALLING);
    digitalWrite(outPorts[3], LOW);
    waitForEdge(0, RISING);
    digitalWrite(outPorts[3], HIGH);
  }

  for (int i = 0; i < 3; i++) {
    waitForEdge(key.scan, FALLING);
    digitalWrite(outPorts[key.out], LOW);
    waitForEdge(key.scan, RISING);
    digitalWrite(outPorts[key.out], HIGH);

    if (key.mod & MOD_SHIFT) {
      waitForEdge(8, FALLING);
      digitalWrite(outPorts[6], LOW);
      waitForEdge(8, RISING);
      digitalWrite(outPorts[6], HIGH);
    }

    if (key.mod & MOD_CODE) {
      waitForEdge(0, FALLING);
      digitalWrite(outPorts[3], LOW);
      waitForEdge(0, RISING);
      digitalWrite(outPorts[3], HIGH);
    }
  }

  waitForEdge(key.scan, FALLING);
  for (int i = 0; i < 3; i++) {
    waitForEdge(key.scan, RISING);
    waitForEdge(key.scan, FALLING);
  }
}
