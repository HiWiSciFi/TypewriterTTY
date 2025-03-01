#include "PseudoTTY.hpp"

#include <fcntl.h>
#include <poll.h>
#include <pty.h>
#include <signal.h>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

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
	if (!this->config->pty.enabled) return false;

	pollfd pfd = {
		.fd = this->master,
		.events = POLLIN,
		.revents = 0
	};
	if (poll(&pfd, 1, 0) == -1) Util::ThrowErrno();
	return (pfd.revents & POLLIN) > 0;
}

#include <iostream>
void PseudoTTY::WriteCodepoint(char32_t codepoint) {
	
	char8_t buf[4];
	uint8_t length = Util::CodepointGetUTF8(codepoint, buf);
	
	std::cout << "len: " << static_cast<int>(length) << " chars:";
	for (int i = 0; i < length; i++) {
		std::cout << " " << std::hex << static_cast<int>(buf[i]);
	}
	std::cout << std::endl;

	if (!this->config->pty.enabled) return;

	if (write(this->master, buf, length) == -1)
		Util::ThrowErrno();
}

// TODO: maybe rework if fcntl gets removed
char32_t PseudoTTY::ReadCodepoint() {
	if (!this->config->pty.enabled) return 0;

	char8_t buf[4];
	char32_t codepoint = 0;

	if (read(this->master, buf, 1) == -1) {
		if (errno == EWOULDBLOCK) return codepoint;
		Util::ThrowErrno();
	}

	uint8_t length = Util::UTF8GetByteLength(buf[0]);

	if (read(this->master, &buf[1], length - 1) == -1) {
		if (errno == EWOULDBLOCK)
			throw std::runtime_error("unexpected end if UTF-8 stream");
		Util::ThrowErrno();
	}

	codepoint = Util::UTF8GetCodepoint(buf, length);

	return codepoint;
}

void PseudoTTY::Open() {
	if (!this->config->pty.enabled) return;
	
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
		if (fcntl(this->master, F_SETFL, O_NONBLOCK) == -1)
			Util::ThrowErrno();
		break;
	}
}

void PseudoTTY::Interrupt() {
	if (!this->config->pty.enabled) return;
	kill(this->childPid, SIGINT);
}
