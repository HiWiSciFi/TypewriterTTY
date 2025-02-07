#ifndef __KEYMAP_HPP
#define __KEYMAP_HPP

#include <inttypes.h>

struct KeymapEntry {
	uint8_t scan;
	uint8_t out;
	uint8_t mod : 7;
	bool valid : 1;
} __attribute__((__packed__));

#define MOD_NONE  0x00
#define MOD_SHIFT 0x01
#define MOD_CODE  0x02

#define KEY_RETURN    0x80 // CRLF
#define KEY_DEL_WORD  0x81 // WORD OUT
#define KEY_MICRO     0x9B // µ

// TODO: include commented non-ascii keys
static KeymapEntry keymap[] = {
	{ 9, 9, MOD_NONE,  false }, // 0x00 NUL
	{ 9, 9, MOD_NONE,  false }, // 0x01 Start of heading
	{ 9, 9, MOD_NONE,  false }, // 0x02 Start of text
	{ 9, 9, MOD_NONE,  false }, // 0x03 End of text
	{ 9, 9, MOD_NONE,  false }, // 0x04 End of transmission
	{ 9, 9, MOD_NONE,  false }, // 0x05 Enquiry
	{ 9, 9, MOD_NONE,  false }, // 0x06 Acknowledge
	{ 9, 9, MOD_NONE,  false }, // 0x07 Bell
	{ 6, 7, MOD_NONE,  true  }, // 0x08 Backspace
	{ 9, 9, MOD_NONE,  false }, // 0x09 Horizontal Tab
	{ 9, 9, MOD_NONE,  false }, // 0x0A LF
	{ 9, 9, MOD_NONE,  false }, // 0x0B Vertical Tab
	{ 9, 9, MOD_NONE,  false }, // 0x0C NP Form feed / New page
	{ 9, 9, MOD_NONE,  false }, // 0x0D CR
	{ 9, 9, MOD_NONE,  false }, // 0x0E Shift out
	{ 9, 9, MOD_NONE,  false }, // 0x0F Shift in
	{ 9, 9, MOD_NONE,  false }, // 0x10 Data link escape
	{ 9, 9, MOD_NONE,  false }, // 0x11 Device control 1
	{ 9, 9, MOD_NONE,  false }, // 0x12 Device control 2
	{ 9, 9, MOD_NONE,  false }, // 0x13 Device control 3
	{ 9, 9, MOD_NONE,  false }, // 0x14 Device control 4
	{ 9, 9, MOD_NONE,  false }, // 0x15 Negative acknowledge
	{ 9, 9, MOD_NONE,  false }, // 0x16 Synchronous idle
	{ 9, 9, MOD_NONE,  false }, // 0x17 End of trans. block
	{ 9, 9, MOD_NONE,  false }, // 0x18 Cancel
	{ 9, 9, MOD_NONE,  false }, // 0x19 End of medium
	{ 9, 9, MOD_NONE,  false }, // 0x1A Substitute
	{ 9, 9, MOD_NONE,  false }, // 0x1B Escape
	{ 9, 9, MOD_NONE,  false }, // 0x1C File separator
	{ 9, 9, MOD_NONE,  false }, // 0x1D Group separator
	{ 9, 9, MOD_NONE,  false }, // 0x1E Record separator
	{ 9, 9, MOD_NONE,  false }, // 0x1F Unit separator
	{ 7, 7, MOD_NONE,  true  }, // 0x20 SPACE
	{ 2, 0, MOD_SHIFT, true  }, // 0x21 !
	{ 2, 1, MOD_SHIFT, true  }, // 0x22 "
	{ 6, 5, MOD_NONE,  true  }, // 0x23 #
	{ 3, 1, MOD_SHIFT, true  }, // 0x24 $
	{ 4, 0, MOD_SHIFT, true  }, // 0x25 %
	{ 4, 1, MOD_SHIFT, true  }, // 0x26 &
	{ 6, 5, MOD_SHIFT, true  }, // 0x27 '
	{ 5, 1, MOD_SHIFT, true  }, // 0x28 (
	{ 6, 0, MOD_SHIFT, true  }, // 0x29 )
	{ 7, 3, MOD_SHIFT, true  }, // 0x2A *
	{ 7, 3, MOD_NONE,  true  }, // 0x2B +
	{ 4, 7, MOD_NONE,  true  }, // 0x2C ,
	{ 5, 7, MOD_NONE,  true  }, // 0x2D -
	{ 5, 6, MOD_NONE,  true  }, // 0x2E .
	{ 5, 0, MOD_SHIFT, true  }, // 0x2F /
	{ 6, 1, MOD_NONE,  true  }, // 0x30 0
	{ 2, 0, MOD_NONE,  true  }, // 0x31 1
	{ 2, 1, MOD_NONE,  true  }, // 0x32 2
	{ 3, 0, MOD_NONE,  true  }, // 0x33 3
	{ 3, 1, MOD_NONE,  true  }, // 0x34 4
	{ 4, 0, MOD_NONE,  true  }, // 0x35 5
	{ 4, 1, MOD_NONE,  true  }, // 0x36 6
	{ 5, 0, MOD_NONE,  true  }, // 0x37 7
	{ 5, 1, MOD_NONE,  true  }, // 0x38 8
	{ 6, 0, MOD_NONE,  true  }, // 0x39 9
	{ 5, 6, MOD_SHIFT, true  }, // 0x3A :
	{ 4, 7, MOD_SHIFT, true  }, // 0x3B ;
	{ 9, 9, MOD_NONE,  false }, // 0x3C <
	{ 6, 1, MOD_SHIFT, true  }, // 0x3D =
	{ 9, 9, MOD_CODE,  true  }, // 0x3E >
	{ 6, 6, MOD_SHIFT, true  }, // 0x3F ?
	{ 9, 9, MOD_NONE,  false }, // 0x40 @
	{ 1, 4, MOD_SHIFT, true  }, // 0x41 A
	{ 3, 6, MOD_SHIFT, true  }, // 0x42 B
	{ 2, 6, MOD_SHIFT, true  }, // 0x43 C
	{ 2, 4, MOD_SHIFT, true  }, // 0x44 D
	{ 2, 2, MOD_SHIFT, true  }, // 0x45 E
	{ 2, 5, MOD_SHIFT, true  }, // 0x46 F
	{ 3, 4, MOD_SHIFT, true  }, // 0x47 G
	{ 3, 5, MOD_SHIFT, true  }, // 0x48 H
	{ 5, 3, MOD_SHIFT, true  }, // 0x49 I
	{ 4, 4, MOD_SHIFT, true  }, // 0x4A J
	{ 4, 5, MOD_SHIFT, true  }, // 0x4B K
	{ 5, 4, MOD_SHIFT, true  }, // 0x4C L
	{ 4, 6, MOD_SHIFT, true  }, // 0x4D M
	{ 3, 7, MOD_SHIFT, true  }, // 0x4E N
	{ 5, 2, MOD_SHIFT, true  }, // 0x4F O
	{ 6, 3, MOD_SHIFT, true  }, // 0x50 P
	{ 1, 2, MOD_SHIFT, true  }, // 0x51 Q
	{ 3, 3, MOD_SHIFT, true  }, // 0x52 R
	{ 1, 5, MOD_SHIFT, true  }, // 0x53 S
	{ 3, 2, MOD_SHIFT, true  }, // 0x54 T
	{ 4, 2, MOD_SHIFT, true  }, // 0x55 U
	{ 2, 7, MOD_SHIFT, true  }, // 0x56 V
	{ 2, 3, MOD_SHIFT, true  }, // 0x57 W
	{ 1, 7, MOD_SHIFT, true  }, // 0x58 X
	{ 1, 6, MOD_SHIFT, true  }, // 0x59 Y
	{ 4, 3, MOD_SHIFT, true  }, // 0x5A Z
	{ 9, 9, MOD_NONE,  false }, // 0x5B [
	{ 9, 9, MOD_NONE,  false }, // 0x5C /* \ */
	{ 9, 9, MOD_NONE,  false }, // 0x5D ]
	{ 9, 9, MOD_NONE,  false }, // 0x5E ^
	{ 5, 7, MOD_SHIFT, true  }, // 0x5F _
	{ 7, 1, MOD_SHIFT, true  }, // 0x60 `
	{ 1, 4, MOD_NONE,  true  }, // 0x61 a
	{ 3, 6, MOD_NONE,  true  }, // 0x62 b
	{ 2, 6, MOD_NONE,  true  }, // 0x63 c
	{ 2, 4, MOD_NONE,  true  }, // 0x64 d
	{ 2, 2, MOD_NONE,  true  }, // 0x65 e
	{ 2, 5, MOD_NONE,  true  }, // 0x66 f
	{ 3, 4, MOD_NONE,  true  }, // 0x67 g
	{ 3, 5, MOD_NONE,  true  }, // 0x68 h
	{ 5, 3, MOD_NONE,  true  }, // 0x69 i
	{ 4, 4, MOD_NONE,  true  }, // 0x6A j
	{ 4, 5, MOD_NONE,  true  }, // 0x6B k
	{ 5, 4, MOD_NONE,  true  }, // 0x6C l
	{ 4, 6, MOD_NONE,  true  }, // 0x6D m
	{ 3, 7, MOD_NONE,  true  }, // 0x6E n
	{ 5, 2, MOD_NONE,  true  }, // 0x6F o
	{ 6, 3, MOD_NONE,  true  }, // 0x70 p
	{ 1, 2, MOD_NONE,  true  }, // 0x71 q
	{ 3, 3, MOD_NONE,  true  }, // 0x72 r
	{ 1, 5, MOD_NONE,  true  }, // 0x73 s
	{ 3, 2, MOD_NONE,  true  }, // 0x74 t
	{ 4, 2, MOD_NONE,  true  }, // 0x75 u
	{ 2, 7, MOD_NONE,  true  }, // 0x76 v
	{ 2, 3, MOD_NONE,  true  }, // 0x77 w
	{ 1, 7, MOD_NONE,  true  }, // 0x78 x
	{ 1, 6, MOD_NONE,  true  }, // 0x79 y
	{ 4, 3, MOD_NONE,  true  }, // 0x7A z
	{ 9, 9, MOD_NONE,  false }, // 0x7B {
	{ 9, 9, MOD_NONE,  false }, // 0x7C |
	{ 9, 9, MOD_NONE,  false }, // 0x7D }
	{ 9, 9, MOD_NONE,  false }, // 0x7E ~
	{ 9, 9, MOD_NONE,  false }, // 0x7F DEL

	{ 7, 4, MOD_NONE,  true  }, // 0x80 CRLF
	{ 0, 7, MOD_NONE,  true  }, // 0x81 WORD OUT

	{ 1, 0, MOD_NONE,  true  }, // 0x82 Case Open
	{ 0, 0, MOD_NONE,  true  }, // 0x83 Pitch
	{ 0, 1, MOD_NONE,  true  }, // 0x84 Line
	{ 0, 2, MOD_NONE,  true  }, // 0x85 LMAR
	{ 0, 2, MOD_CODE,  true  }, // 0x86 RMAR
	{ 0, 3, MOD_NONE,  true  }, // 0x87 CODE
	{ 0, 4, MOD_NONE,  true  }, // 0x88 T+
	{ 0, 4, MOD_CODE,  true  }, // 0x89 T-
	{ 0, 5, MOD_NONE,  true  }, // 0x8A Caps Lock
	{ 0, 7, MOD_CODE,  true  }, // 0x8B LINE OUT
	{ 1, 1, MOD_CODE,  true  }, // 0x8C L IND Top
	{ 1, 3, MOD_CODE,  true  }, // 0x8D L IND Bot
	{ 1, 1, MOD_NONE,  true  }, // 0x8E Return L Top
	{ 1, 3, MOD_NONE,  true  }, // 0x8F Return L Bot
	{ 6, 7, MOD_CODE,  true  }, // 0x90 DEL?
	{ 7, 0, MOD_NONE,  true  }, // 0x91 <-||->
	{ 7, 2, MOD_NONE,  true  }, // 0x92 RELOC
	{ 7, 2, MOD_CODE,  true  }, // 0x93 |-<-|
	{ 7, 5, MOD_NONE,  true  }, // 0x94 |<-|
	{ 7, 5, MOD_CODE,  true  }, // 0x95 <<-
	{ 7, 6, MOD_NONE,  true  }, // 0x96 INDEX
	{ 7, 6, MOD_CODE,  true  }, // 0x97 REV

	{ 8, 6, MOD_NONE,  true  }, // 0x98 SHIFT L R

	{ 3, 0, MOD_SHIFT, true  }, // 0x99 §
	{ 7, 1, MOD_NONE,  true  }, // 0x9A ´
	{ 4, 2, MOD_CODE,  true  }, // 0x9B µ
	{ 1, 7, MOD_CODE,  true  }, // 0x9C ²
	{ 2, 7, MOD_CODE,  true  }, // 0x9D ³
	{ 2, 3, MOD_CODE,  true  }, // 0x9E °
	{ 6, 4, MOD_NONE,  true  }, // 0x9F ä
	{ 6, 4, MOD_SHIFT, true  }, // 0xA0 Ä
	{ 5, 5, MOD_NONE,  true  }, // 0xA1 ö
	{ 5, 5, MOD_SHIFT, true  }, // 0xA2 Ö
	{ 6, 2, MOD_NONE,  true  }, // 0xA3 ü
	{ 6, 2, MOD_SHIFT, true  }, // 0xA4 Ü
	{ 6, 6, MOD_NONE,  true  }, // 0xA5 ß
};

#endif // __KEYMAP_HPP
