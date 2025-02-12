#include <iostream>
#include <memory>

#include "PseudoTTY.hpp"
#include "Config.hpp"
#include "Printer.hpp"

static constexpr const char* KEYBOARD_CONFIG_PATH = "config/keyboard.toml";
static constexpr const char* PRINTER_CONFIG_PATH  = "config/printer.toml";
static constexpr const char* TERMINAL_CONFIG_PATH = "config/terminal.toml";

int main(int argc, char** argv) {
	std::cout << "Loading config files..." << std::endl;
	std::cout << "Keyboard..." << std::endl;
	auto keyboardCfg = std::make_shared<KeyboardConfig>(KEYBOARD_CONFIG_PATH);
	std::cout << "Printer..." << std::endl;
	auto printerCfg = std::make_shared<PrinterConfig>(PRINTER_CONFIG_PATH);
	std::cout << "Terminal..." << std::endl;
	auto terminalCfg = std::make_shared<TerminalConfig>(TERMINAL_CONFIG_PATH);
	std::cout << "Config files loaded." << std::endl;

	std::cout << "Connecting to Arduino..." << std::endl;
	Printer printer(printerCfg);
	std::cout << "Waiting for Typewriter to become active..." << std::endl;
	printer.WaitForAvailable();
	std::cout << "Typewriter available." << std::endl;

	std::cout << "Prepare shell environment..." << std::endl;
	PseudoTTY pty(terminalCfg);
	std::cout << "Start shell..." << std::endl;
	pty.Open();

	pid_t pid = fork();

	switch (pid) {
		case -1: break; // error
		case 0:  break; // child
		default: break; // parent
	}
}
