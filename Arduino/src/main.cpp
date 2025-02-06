#include <Arduino.h>
#include "Keyboard.hpp"

uint8_t scanPorts[9] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
uint8_t outPorts[8] = { 21, 20, 19, 18, 17, 16, 15, 14 };

// uint8_t scanPorts[9] = { 45, 46, 47, 48, 49, 50, 51, 52, 53 };
// uint8_t outPorts[8] = { 34, 35, 36, 37, 38, 39, 40, 41 };

#define ASCII_ACK 0x06
#define ASCII_NAK 0x15

#define ASIZE(arr) (sizeof( arr ) / sizeof( arr[0] ))

// TODO: consider using INPUT_PULLUP
void setup() {
  Serial.begin(921600);
  while (!Serial);

  for (uint8_t i = 0; i < ASIZE(scanPorts); i++) pinMode(scanPorts[i], INPUT);
  for (uint8_t i = 0; i < ASIZE(outPorts); i++) {
    pinMode(outPorts[i], OUTPUT);
    digitalWrite(outPorts[i], HIGH);
  }
}

void loop() {
  while (Serial.available() > 0) {
    uint8_t c = (uint8_t)Serial.read();
    Serial.print(ASCII_ACK);
    writeKey(c);
  }

  // writeKey(KEY_RETURN);

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
