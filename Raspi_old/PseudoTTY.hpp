#ifndef __PSEUDOTTY_HPP
#define __PSEUDOTTY_HPP

#include <cstdint>
#include <string>
#include <sys/ioctl.h>
#include <vector>

class PseudoTTY {
private:
	int master = -1;
	pid_t childPid = -1;
	winsize winp;
	std::vector<std::string> args;
	std::vector<char*> env;

	static void throwErrno();

public:
	// throws: std::runtime_error
	PseudoTTY(unsigned short columns, unsigned short rows, const std::vector<std::string>& args, const std::vector<char*>& env);

	~PseudoTTY();

	bool dataAvailable();

	// throws: std::runtime_error
	void writeTTY(const std::string& msg);

	// throws: std::runtime_error
	void writeTTY(char c);

	//throws: std::runtime_error
	void writeTTYCodepoint(uint32_t codepoint);

	// throws: std::runtime_error
	std::string readTTY();

	// throws: std::runtime_error
	uint32_t readCodepointTTY();

	// throws: std::runtime_error
	void openTTY();
};

#endif // __PSEUDOTTY_HPP
