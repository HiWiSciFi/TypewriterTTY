#ifndef __PSEUDOTTY_HPP
#define __PSEUDOTTY_HPP

#include <vector>
#include <string>
#include <sys/ioctl.h>
#include <cstdint>

class PseudoTTY {
private:
	int master = -1;
	pid_t childPid = -1;
	winsize winp;
	std::vector<std::string> args;
	std::vector<char*> env;

public:
	// throws
	PseudoTTY(unsigned short columns, unsigned short rows, const std::vector<std::string>& args, const std::vector<char*>& env);

	~PseudoTTY();

	bool dataAvailable();

	// throws
	void writeCodepoint(char32_t codepoint);

	// throws
	char32_t readCodepoint();

	//throws
	void open();
};

#endif // __PSEUDOTTY_HPP
