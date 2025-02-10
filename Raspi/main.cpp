#include <iostream>
#include <unistd.h>

#include "Keyboard.hpp"
#include "Printer.hpp"
#include "PseudoTTY.hpp"

// +-----+-----+---------+------+---+Pi Zero 2W+---+------+---------+-----+-----+
// | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
// +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
// |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
// |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
// |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
// |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 0 | IN   | TxD     | 15  | 14  |
// |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
// |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
// |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
// |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
// |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
// |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
// |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
// |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
// |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
// |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
// |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
// |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
// |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
// |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
// |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
// |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
// +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
// | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
// +-----+-----+---------+------+---+Pi Zero 2W+---+------+---------+-----+-----+

#include <cstring>
#include <bit>
int main(int argc, char** argv) {
	// I/O pins for keyboard scanning
	static const std::vector<int> pinsScan = { 22, 10, 9, 11, 5, 6, 13, 19, 26 };
	static const std::vector<int> pinsOut = { 25, 8, 7, 1, 12, 16, 20, 21 };

	// set environment variables
	std::vector<char*> myenv;
	int envCount = 0;
	for (; environ[envCount] != nullptr; envCount++);
	myenv.reserve(envCount + 2); // counted envs + potential TERM + nullptr (appended in PTY constructor)
	for (int i = 0; environ[i] != nullptr; i++) {
		if (strlen(environ[i]) >= 5 && strncmp(environ[i], "TERM=", 5) == 0)
			continue;
		myenv.push_back(environ[i]);
	}
	myenv.push_back(const_cast<char*>("TERM=dumb"));

	try {
		// initialize handlers
		Keyboard keyboard(pinsScan, pinsOut);
		Printer printer("/dev/ttyACM0", 921600);
		PseudoTTY pty(75, 1, { "/bin/bash" }, myenv);
		pty.openTTY();
		sleep(1); // give bash time to start up

		// save last pressed key to prevent hold spamming
		KeymapEntry lastKey = { 0x00, 0x00 };

		// app loop
		while (true) {
			try {
				// print available pty content
				while (pty.dataAvailable()) {
					uint32_t codepoint = pty.readCodepointTTY();
					if (codepoint != 0x00) printer.print(codepoint);
				}
			}
			catch (std::runtime_error e) {
				std::cerr << "ERROR: " << e.what() << std::endl;
			}

			try {
				// read keyboard key
				KeymapEntry key = keyboard.readKey();
				if (key == lastKey) continue;
				lastKey = key; // assign key as last pressed
				if (key == KeymapEntry{ 0x00, 0x00 }) continue;

				std::cout << "U+" << std::hex << key.codepoint << " 0x" << std::hex << static_cast<int>(key.key)
						  << " c:" << static_cast<char>(key.codepoint) << std::endl;

				pty.writeTTYCodepoint(key.codepoint);
			}
			catch (std::runtime_error e) {
				std::cerr << "ERROR: " << e.what() << std::endl;
			}
		}
	}
	catch (std::runtime_error e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		exit(1);
	}
}
