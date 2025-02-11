#include <iostream>

#include "PseudoTTY.hpp"
#include "Config.hpp"

int main(int argc, char** argv) {
	// I/O pins for keyboard scanning
	static const std::vector<int> pinsScan = { 22, 10, 9, 11, 5, 6, 13, 19, 26 };
	static const std::vector<int> pinsOut = { 25, 8, 7, 1, 12, 16, 20, 21 };

	// read config

	// PseudoTTY pty(75, 1, { "/bin/bash" }, { });
	// pty.open();

	KeyboardConfig keyboardCfg("Raspi/keyboard.toml");
}
