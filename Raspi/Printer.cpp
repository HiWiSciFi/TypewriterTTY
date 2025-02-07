#include "Printer.hpp"

#include <wiringSerial.h>
#include <stdexcept>

Printer::Printer(const std::string& serialPort, int baud) {
    this->initialized = false;
    this->serialPort = serialPort;
    this->baud = baud;

    if ((this->fd = serialOpen(this->serialPort.c_str(), this->baud)) < 0)
        throw std::runtime_error("Failed to open serial port");

    this->initialized = true;
}

Printer::~Printer() {
    if (this->initialized) serialClose(this->fd);
}

#include <iostream>
#include <bit>
void Printer::print(uint32_t codepoint) {
    // if (!unicodeMap.contains(codepoint)) return; // TODO: indicate error
    if (!unicodeMap.contains(codepoint)) codepoint = 0x3F; // '?'

    const char8_t* characters = unicodeMap.at(codepoint);
    for (int curr = 0; characters[curr] != u8'\0'; curr++) {
        std::cout << std::bit_cast<char>(characters[curr]) << std::flush;
        serialPutchar(this->fd, characters[curr]);
    }
    // serialFlush(this->fd); // This crashes the PI (or at least its ethernet connection)

    while (!serialDataAvail(this->fd));

    int response = serialGetchar(this->fd);
    switch (response) {
    case 0x06: // ACK
        // std::cout << " ACK " << std::flush;
        break;
    case 0x15: // NAK
        // TODO: indicate error
        std::cout << " NAK " << std::flush;
        // throw std::runtime_error("character could not be printed");
        break;
    default:
        throw std::runtime_error("invalid response over serial");
        break;
    }
}
