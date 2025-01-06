#include <Arduino.h>

uint8_t scanPorts[9] = { 45, 46, 47, 48, 49, 50, 51, 52, 53 };
uint8_t outPorts[8]  = { 34, 35, 36, 37, 38, 39, 40, 41 };

#define ASIZE(arr) (sizeof( arr ) / sizeof( arr[0] ))

typedef struct KeymapEntry {
  uint8_t scan;
  uint8_t out;
  uint8_t mod;
};

#define MOD_NONE  0x00
#define MOD_SHIFT 0x01
#define MOD_CODE  0x02

#define KEY_RETURN 0x3C // ASCII '<'

// index = char - 0x20
// TODO: include commented non-ascii keys
KeymapEntry keymap[] = {
  // { 3, 0, MOD_SHIFT }, // §
  // { 7, 1, MOD_NONE  }, // ´
  // { 4, 2, MOD_CODE  }, µ
  // { 1, 7, MOD_CODE  }, ²
  // { 2, 7, MOD_CODE  }, ³
  // { 2, 3, MOD_CODE  }, °
  // { 6, 4, MOD_NONE  }, // ä
  // { 6, 4, MOD_SHIFT }, // Ä
  // { 5, 5, MOD_NONE  }, // ö
  // { 5, 5, MOD_SHIFT }, // Ö
  // { 6, 2, MOD_NONE  }, // ü
  // { 6, 2, MOD_SHIFT }, // Ü
  // { 6, 6, MOD_NONE  }, // ß

  // { 1, 0, MOD_NONE  }, // Case Open
  // { 0, 0, MOD_NONE  }, // Pitch
  // { 0, 1, MOD_NONE  }, // Line
  // { 0, 2, MOD_NONE  }, // LMAR
  // { 0, 2, MOD_CODE  }, // RMAR
  // { 0, 3, MOD_NONE  }, // CODE
  // { 0, 4, MOD_NONE  }, // T+
  // { 0, 4, MOD_CODE  }, // T-
  // { 0, 5, MOD_NONE  }, // Caps Lock
  // { 0, 7, MOD_NONE  }, // WORD OUT
  // { 0, 7, MOD_CODE  }, // LINE OUT
  // { 1, 1, MOD_CODE  }, // L IND Top
  // { 1, 3, MOD_CODE  }, // L IND Bot
  // { 1, 1, MOD_NONE  }, // Return L Top
  // { 1, 3, MOD_NONE  }, // Return L Bot
  // { 6, 7, MOD_NONE  }, // Backspace?
  // { 6, 7, MOD_CODE  }, // DEL?
  // { 7, 0, MOD_NONE  }, // <-||->
  // { 7, 2, MOD_NONE  }, // RELOC
  // { 7, 2, MOD_CODE  }, // |-<-|
  // { 7, 5, MOD_NONE  }, // |<-|
  // { 7, 5, MOD_CODE  }, // <<-
  // { 7, 6, MOD_NONE  }, // INDEX
  // { 7, 6, MOD_CODE  }, // REV

  // { 8, 6, MOD_NONE  }, // SHIFT L R

  { 0, 6, MOD_NONE  }, // 0x20 SPACE L
  // { 7, 7, MOD_NONE  }, // 0x20 SPACE R
  { 2, 0, MOD_SHIFT }, // 0x21 !
  { 2, 1, MOD_SHIFT }, // 0x22 "
  { 6, 5, MOD_NONE  }, // 0x23 #
  { 3, 1, MOD_SHIFT }, // 0x24 $
  { 4, 0, MOD_SHIFT }, // 0x25 %
  { 4, 1, MOD_SHIFT }, // 0x26 &
  { 6, 5, MOD_SHIFT }, // 0x27 '
  { 5, 1, MOD_SHIFT }, // 0x28 (
  { 6, 0, MOD_SHIFT }, // 0x29 )
  { 7, 3, MOD_SHIFT }, // 0x2A *
  { 7, 3, MOD_NONE  }, // 0x2B +
  { 4, 7, MOD_NONE  }, // 0x2C ,
  { 5, 7, MOD_NONE  }, // 0x2D -
  { 5, 6, MOD_NONE  }, // 0x2E .
  { 5, 0, MOD_SHIFT }, // 0x2F /
  { 6, 1, MOD_NONE  }, // 0x30 0
  { 2, 0, MOD_NONE  }, // 0x31 1
  { 2, 1, MOD_NONE  }, // 0x32 2
  { 3, 0, MOD_NONE  }, // 0x33 3
  { 3, 1, MOD_NONE  }, // 0x34 4
  { 4, 0, MOD_NONE  }, // 0x35 5
  { 4, 1, MOD_NONE  }, // 0x36 6
  { 5, 0, MOD_NONE  }, // 0x37 7
  { 5, 1, MOD_NONE  }, // 0x38 8
  { 6, 0, MOD_NONE  }, // 0x39 9
  { 5, 6, MOD_SHIFT }, // 0x3A :
  { 4, 7, MOD_SHIFT }, // 0x3B ;
  { 7, 4, MOD_NONE  }, // 0x3C CRLF ! ASCII <
  { 6, 1, MOD_SHIFT }, // 0x3D =
  { 255, 255, MOD_NONE  }, // 0x3E > NOT
  { 6, 6, MOD_SHIFT }, // 0x3F ?
  { 255, 255, MOD_NONE  }, // 0x40 @ NOT
  { 1, 4, MOD_SHIFT }, // 0x41 A
  { 3, 6, MOD_SHIFT }, // 0x42 B
  { 2, 6, MOD_SHIFT }, // 0x43 C
  { 2, 4, MOD_SHIFT }, // 0x44 D
  { 2, 2, MOD_SHIFT }, // 0x45 E
  { 2, 5, MOD_SHIFT }, // 0x46 F
  { 3, 4, MOD_SHIFT }, // 0x47 G
  { 3, 5, MOD_SHIFT }, // 0x48 H
  { 5, 3, MOD_SHIFT }, // 0x49 I
  { 4, 4, MOD_SHIFT }, // 0x4A J
  { 4, 5, MOD_SHIFT }, // 0x4B K
  { 5, 4, MOD_SHIFT }, // 0x4C L
  { 4, 6, MOD_SHIFT }, // 0x4D M
  { 3, 7, MOD_SHIFT }, // 0x4E N
  { 5, 2, MOD_SHIFT }, // 0x4F O
  { 6, 3, MOD_SHIFT }, // 0x50 P
  { 1, 2, MOD_SHIFT }, // 0x51 Q
  { 3, 3, MOD_SHIFT }, // 0x52 R
  { 1, 5, MOD_SHIFT }, // 0x53 S
  { 3, 2, MOD_SHIFT }, // 0x54 T
  { 4, 2, MOD_SHIFT }, // 0x55 U
  { 2, 7, MOD_SHIFT }, // 0x56 V
  { 2, 3, MOD_SHIFT }, // 0x57 W
  { 1, 7, MOD_SHIFT }, // 0x58 X
  { 1, 6, MOD_SHIFT }, // 0x59 Y
  { 4, 3, MOD_SHIFT }, // 0x5A Z
  { 255, 255, MOD_NONE  }, // 0x5B [ NOT
  { 255, 255, MOD_NONE  }, // 0x5C /* \ */ NOT
  { 255, 255, MOD_NONE  }, // 0x5D ] NOT
  { 255, 255, MOD_NONE  }, // 0x5E ^ NOT
  { 5, 7, MOD_SHIFT }, // 0x5F _
  { 7, 1, MOD_SHIFT }, // 0x60 `
  { 1, 4, MOD_NONE  }, // 0x61 a
  { 3, 6, MOD_NONE  }, // 0x62 b
  { 2, 6, MOD_NONE  }, // 0x63 c
  { 2, 4, MOD_NONE  }, // 0x64 d
  { 2, 2, MOD_NONE  }, // 0x65 e
  { 2, 5, MOD_NONE  }, // 0x66 f
  { 3, 4, MOD_NONE  }, // 0x67 g
  { 3, 5, MOD_NONE  }, // 0x68 h
  { 5, 3, MOD_NONE  }, // 0x69 i
  { 4, 4, MOD_NONE  }, // 0x6A j
  { 4, 5, MOD_NONE  }, // 0x6B k
  { 5, 4, MOD_NONE  }, // 0x6C l
  { 4, 6, MOD_NONE  }, // 0x6D m
  { 3, 7, MOD_NONE  }, // 0x6E n
  { 5, 2, MOD_NONE  }, // 0x6F o
  { 6, 3, MOD_NONE  }, // 0x70 p
  { 1, 2, MOD_NONE  }, // 0x71 q
  { 3, 3, MOD_NONE  }, // 0x72 r
  { 1, 5, MOD_NONE  }, // 0x73 s
  { 3, 2, MOD_NONE  }, // 0x74 t
  { 4, 2, MOD_NONE  }, // 0x75 u
  { 2, 7, MOD_NONE  }, // 0x76 v
  { 2, 3, MOD_NONE  }, // 0x77 w
  { 1, 7, MOD_NONE  }, // 0x78 x
  { 1, 6, MOD_NONE  }, // 0x79 y
  { 4, 3, MOD_NONE  }, // 0x7A z
};

void setup() {
  Serial.begin(921600);

  for (int i = 0; i < ASIZE(scanPorts); i++) pinMode(scanPorts[i], INPUT);
  for (int i = 0; i < ASIZE(outPorts);  i++) {
    pinMode(outPorts[i], OUTPUT);
    digitalWrite(outPorts[i], HIGH);
  }
}

uint8_t lastPin = 0;
uint8_t last = 0;

#define RISING  LOW
#define FALLING HIGH

void waitFor(uint8_t scan, uint8_t state) {
  while (digitalRead(scanPorts[scan]) == state);
}

void writeKey(size_t keycode) {
  KeymapEntry key = keymap[keycode - 0x20];
  for (int i = 0; i < 2; i++) {
    waitFor(key.scan, FALLING);
    digitalWrite(outPorts[key.out], LOW);
    waitFor(key.scan, RISING);
    digitalWrite(outPorts[key.out], HIGH);
  }
  waitFor(key.scan, FALLING);
  for (int i = 0; i < 3; i++) {
    waitFor(key.scan, RISING);
    waitFor(key.scan, FALLING);
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
