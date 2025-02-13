#include "PseudoTTY.hpp"

#include <poll.h>
#include <pty.h>
#include <fcntl.h>
#include <sstream>
#include <signal.h>
#include <sys/wait.h>

#include "Util.hpp"

PseudoTTY::PseudoTTY(const std::shared_ptr<TerminalConfig>& config) {
	this->config = config;
}

PseudoTTY::~PseudoTTY() {
	if (this->childPid > 0) {
		if (this->master != -1)
			if (close(this->master) == -1) Util::ThrowErrno();
		if (kill(this->childPid, SIGKILL) == -1) Util::ThrowErrno();
		waitpid(this->childPid, NULL, 0);
	}
}

bool PseudoTTY::DataAvailable() {
	pollfd pfd = {
		.fd = this->master,
		.events = POLLIN,
		.revents = 0
	};
	if (poll(&pfd, 1, 0) == -1) Util::ThrowErrno();
	return (pfd.revents & POLLIN) > 0;
}

void PseudoTTY::WriteCodepoint(char32_t codepoint) {
	char8_t u8chars[4];
	uint8_t size = 0;
	if (codepoint >= 0x0000'0000 && codepoint <= 0x0000'007F) {
		u8chars[0] = codepoint;
		size = 1;
	}
	else if (codepoint >= 0x0000'0080 && codepoint <= 0x0000'07FF) {
		u8chars[0] = (codepoint >> 8) & 0x1F;
		u8chars[1] = codepoint & 0x3F;
		size = 2;
	}
	else if (codepoint >= 0x0000'0800 && codepoint <= 0x0000'7FFF) {
		u8chars[0] = (codepoint >> 16) & 0x0F;
		u8chars[1] = (codepoint >> 8) & 0x3F;
		u8chars[2] = codepoint & 0x3F;
		size = 3;
	}
	else if (codepoint >= 0x0001'0000 && codepoint <= 0x0010'FFFF) {
		u8chars[0] = (codepoint >> 24) & 0x07;
		u8chars[1] = (codepoint >> 16) & 0x3F;
		u8chars[2] = (codepoint >> 8) & 0x3F;
		u8chars[3] = codepoint & 0x3F;
		size = 4;
	}
	else {
		std::stringstream ss;
		ss << "invalid unicode codepoint U+" << std::hex << static_cast<uint32_t>(codepoint);
		throw std::runtime_error(ss.str());
	}

	if (write(this->master, u8chars, size) == -1)
		Util::ThrowErrno();
}

// TODO: maybe rework if fcntl gets removed
char32_t PseudoTTY::ReadCodepoint() {
	char8_t buf[4];
	char32_t codepoint = 0;

	if (read(this->master, buf, 1) == -1) {
		if (errno == EWOULDBLOCK) return codepoint;
		Util::ThrowErrno();
	}

	uint8_t size = 0;
	if ((buf[0] & 0b1000'0000) == 0b0000'0000)
		size = 0;
	else if ((buf[0] & 0b1110'0000) == 0b1100'0000)
		size = 1;
	else if ((buf[0] & 0b1111'0000) == 0b1110'0000)
		size = 2;
	else if ((buf[0] & 0b1111'1000) == 0b1111'0000)
		size = 3;
	else {
		std::stringstream ss;
		ss << "invalid UTF-8 starting Byte 0x" << std::hex << static_cast<int>(buf[0]);
		throw std::runtime_error(ss.str());
	}

	static char8_t fbMasks[] = { 0b0111'1111, 0b0001'1111, 0b0000'1111, 0b0000'0111 };
	char8_t fbMask = fbMasks[size];

	codepoint = buf[0] & fbMask;

	if (read(this->master, &buf[1], size) == -1) {
		if (errno == EWOULDBLOCK)
			throw std::runtime_error("unexpected end of UTF-8 stream");
		Util::ThrowErrno();
	}

	for (int8_t i = 0; i < size; i++) {
		if ((buf[i] & 0b1100'0000) != 0b1000'0000) {
			std::stringstream ss;
			ss << "invalid UTF-8 continuation Byte 0x" << std::hex << static_cast<int>(buf[i]);
			throw std::runtime_error(ss.str());
		}
		codepoint <<= 6;
		codepoint |= buf[i] & 0b0011'1111;
	}

	return codepoint;
}

void PseudoTTY::Open() {
	winsize winp = {
		.ws_row = this->config->window.rows,
		.ws_col = this->config->window.columns,
		.ws_xpixel = 0,
		.ws_ypixel = 0
	};
	// TODO: add termios
	this->childPid = forkpty(&this->master, NULL, NULL, &winp);

	switch (this->childPid) {
	case -1:
		Util::ThrowErrno();
		break;
	case 0:
	{
		// child process

		// arrange env vars
		std::vector<char*> envp;
		envp.reserve(this->config->environment.size() + 1);
		for (size_t i = 0; i < this->config->environment.size(); i++)
			envp.push_back(this->config->environment[i].data());
		envp.push_back(nullptr);

		// arrange args
		std::vector<char*> argv;
		argv.reserve(this->config->shell.arguments.size() + 1);
		for (size_t i = 0; i < this->config->shell.arguments.size(); i++)
			argv.push_back(this->config->shell.arguments[i].data());
		argv.push_back(nullptr);

		// TODO: handle termination
		execvpe(this->config->shell.binary.c_str(), argv.data(), envp.data());

		break;
	}
	default:
		// parent process
		// TODO check following lines for necessity
		// if (fcntl(this->master, F_SETFL, O_NONBLOCK) == -1)
		// 	Util::ThrowErrno();
		break;
	}
}
