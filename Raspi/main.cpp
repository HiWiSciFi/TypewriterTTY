#include <iostream>
#include <memory>

#include "Config.hpp"
#include "Keyboard.hpp"
#include "Printer.hpp"
#include "PseudoTTY.hpp"
#include "Util.hpp"

static constexpr const char* KEYBOARD_CONFIG_PATH = "config/keyboard.toml";
static constexpr const char* PRINTER_CONFIG_PATH = "config/printer.toml";
static constexpr const char* TERMINAL_CONFIG_PATH = "config/terminal.toml";

void RunPrinter(Printer& printer, PseudoTTY& pty);
void RunKeyboard(Keyboard& keyboard, PseudoTTY& pty);

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
	// printer.WaitForAvailable();
	std::cout << "Typewriter available." << std::endl;

	std::cout << "Prepare shell environment..." << std::endl;
	PseudoTTY pty(terminalCfg);
	std::cout << "Start shell..." << std::endl;
	pty.Open();

	std::cout << "Done." << std::endl;

	pid_t pid = fork();

	switch (pid) {
	case -1: throw std::runtime_error("failed to fork"); break; // error
	case 0: RunPrinter(printer, pty); break; // child
	default: // parent
	{
		Keyboard keyboard(keyboardCfg);
		RunKeyboard(keyboard, pty);
		break;
	}
	}
}

void RunKeyboard(Keyboard& keyboard, PseudoTTY& pty) {
	keyboard.Setup();

	Keyboard::KeyResult lastKey = { Keyboard::KeyType::NONE, 0x00000000, 0x00 };
	while (true) {
		auto key = keyboard.GetKey();
		if (key == lastKey) continue;
		lastKey = key;

		switch (key.type) {
		case Keyboard::KeyType::UNICODE:
			std::cout << "Pressed U+" << std::hex << static_cast<uint32_t>(key.codepoint) << std::endl;
			pty.WriteCodepoint(key.codepoint);
			break;
		case Keyboard::KeyType::KEYCODE:
			std::cout << "Pressed 0x" << std::hex << static_cast<uint32_t>(key.keycode) << std::endl;
			// TODO
			break;
		default: break;
		}
	}
}

void RunPrinter(Printer& printer, PseudoTTY& pty) {
	while (true) {
		while (!pty.DataAvailable()); // TODO: recheck if fcntl is removed
		char32_t codepoint = pty.ReadCodepoint();
		// printer.PrintCodepoint(codepoint);
	}
}
