#ifndef __PRINTER_HPP
#define __PRINTER_HPP

#include <memory>
#include <string>

#include "Config.hpp"

class Printer {
private:
	int serial;
	bool connected = false;

public:
	Printer(const std::shared_ptr<PrinterConfig>& config);
	~Printer();

	void WaitForAvailable();
};

#endif // __PRINTER_HPP
