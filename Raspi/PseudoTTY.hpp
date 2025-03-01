#ifndef __PSEUDOTTY_HPP
#define __PSEUDOTTY_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <sys/ioctl.h>
#include <vector>

#include "Config.hpp"

class PseudoTTY {
private:
	std::shared_ptr<TerminalConfig> config;
	int master = -1;
	pid_t childPid = -1;

public:
	// throws
	PseudoTTY(const std::shared_ptr<TerminalConfig>& config);

	~PseudoTTY();

	bool DataAvailable();

	// throws
	void WriteCodepoint(char32_t codepoint);

	// throws
	char32_t ReadCodepoint();

	//throws
	void Open();

	void Interrupt();
};

#endif // __PSEUDOTTY_HPP
