#include <Arduino.h>
#include "Keyboard.hpp"

uint8_t scanPorts[9] = { 45, 46, 47, 48, 49, 50, 51, 52, 53 };
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
  writeKey('H');
  writeKey('e');
  writeKey('l');
  writeKey('l');
  writeKey('o');

  writeKey(' ');

  writeKey('w');
  writeKey('o');
  writeKey('r');
  writeKey('l');
  writeKey('d');

  writeKey(KEY_RETURN); // CR LF
  
  delay(2000);
}
