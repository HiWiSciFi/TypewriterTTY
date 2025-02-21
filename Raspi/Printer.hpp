#ifndef __PRINTER_HPP
#define __PRINTER_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "Config.hpp"

class Printer {
private:
	std::shared_ptr<PrinterConfig> config;
	int serial;
	bool connected = false;

public:
	Printer(const std::shared_ptr<PrinterConfig>& config);
	~Printer();

	void WaitForAvailable();

	void PrintCodepoint(char32_t codepoint);
	void PrintKeycode(uint8_t keycode);
};

#endif // __PRINTER_HPP
