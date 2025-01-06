#include <Arduino.h>
#include "Keyboard.hpp"

uint8_t scanPorts[9] = { 53, 52, 51, 50, 49, 48, 47, 46, 45 };
uint8_t outPorts[8]  = { 34, 35, 36, 37, 38, 39, 40, 41 };

#define ASIZE(arr) (sizeof( arr ) / sizeof( arr[0] ))

// TODO: consider using INPUT_PULLUP
void setup() {
  Serial.begin(921600);
  while (!Serial);

  for (uint8_t i = 0; i < ASIZE(scanPorts); i++) pinMode(scanPorts[i], INPUT);
  for (uint8_t i = 0; i < ASIZE(outPorts);  i++) {
    pinMode(outPorts[i], OUTPUT);
    digitalWrite(outPorts[i], HIGH);
  }
}

void loop() {
  while (Serial.available() > 0) {
    uint8_t c = (uint8_t)Serial.read();
    Serial.print("Received: 0x");
    Serial.println(c, HEX);
    switch (c) {
    case '\n':
      c = KEY_RETURN;
      break;
    case '\r':
      return;
    case '\b':
      c = KEY_BACKSPACE;
      break;
    case 0x17:
      c = KEY_DEL_WORD;
      break;
    }
    writeKey(c);
  }

  // writeKey('H');
  // writeKey(KEY_MICRO);
  // writeKey(KEY_BACKSPACE);
  // writeKey('e');
  // writeKey('l');
  // writeKey('l');
  // writeKey('o');

  // writeKey(' ');

  // writeKey('W');
  // writeKey('o');
  // writeKey('r');
  // writeKey('l');
  // writeKey('d');
  // writeKey('!');

  // writeKey(KEY_RETURN); // CR LF
  
  // delay(2000);
}
