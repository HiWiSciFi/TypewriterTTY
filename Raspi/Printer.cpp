#include "Printer.hpp"

#include <wiringSerial.h>
#include <stdexcept>
#include <sstream>

static const constexpr char8_t ASCII_ENQ = 0x05;
static const constexpr char8_t ASCII_ACK = 0x06;
static const constexpr char8_t ASCII_NAK = 0x15;

Printer::Printer(const std::shared_ptr<PrinterConfig>& config) {
	this->config = config;

	if ((this->serial = serialOpen(config->serial.port.c_str(), config->serial.baud)) < 0) {
		std::stringstream ss;
		ss << "failed to open serial port " << config->serial.port
		   << " with " << config->serial.baud << " Baud";
		throw std::runtime_error(ss.str());
	}
	this->connected = true;
}

Printer::~Printer() {
	if (this->connected) serialClose(this->serial);
}

void Printer::WaitForAvailable() {
	serialPutchar(this->serial, ASCII_ENQ);

	// wait for response
	while (!serialDataAvail(this->serial));

	int response = serialGetchar(this->serial);
	if (response != ASCII_ACK) {
		std::stringstream ss;
		ss << "invalid response over serial. Expected 0x" << std::hex << static_cast<int>(ASCII_ACK)
		   << " but received 0x" << std::hex << response;
		throw std::runtime_error(ss.str());
	}
}

void Printer::PrintCodepoint(char32_t codepoint) {
	if (!this->config->translationMap.contains(codepoint))
		codepoint = this->config->printer.translationFallback;

	std::u8string str = this->config->translationMap.at(codepoint);
	for (size_t i = 0; i < str.length(); i++) {
		serialPutchar(this->serial, str.at(i));
		while (!serialDataAvail(this->serial));
		int response = serialGetchar(this->serial);

		if (response != ASCII_ACK) {
			// TODO
		}
	}
}
