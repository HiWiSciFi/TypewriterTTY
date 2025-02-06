#include "PseudoTTY.hpp"

#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <pty.h>
#include <signal.h>
#include <sstream>
#include <stdexcept>
#include <sys/wait.h>
#include <unistd.h>

void PseudoTTY::throwErrno() {
    error_t e = errno;
    errno = 0;
    std::string msg = std::string(strerror(errno));
    if (errno != 0) {
        msg = "failed to retrieve error string. Original error: ";
        msg += e;
    }
    throw std::runtime_error(msg);
}

PseudoTTY::PseudoTTY(unsigned short columns, unsigned short rows, const std::vector<std::string>& args) {
    this->winp = {
        .ws_row = rows,
        .ws_col = columns,
        .ws_xpixel = 0,
        .ws_ypixel = 0
    };
    this->args = args;
}

PseudoTTY::~PseudoTTY() {
    if (this->childPid != -1 && this->childPid != 0) {
        if (this->master != -1)
            if (close(this->master) == -1) perror("error closing pty master");
        if (kill(this->childPid, SIGKILL) == -1) perror("failed to kill child process");
        waitpid(this->childPid, NULL, 0);
    }
}

void PseudoTTY::openTTY() {
    this->childPid = forkpty(&this->master, NULL, NULL, &this->winp);

    if (this->childPid == -1)
        this->throwErrno();

    if (this->childPid == 0) {
        // child process
        std::vector<char*> bargv;
        bargv.reserve(this->args.size() + 1);
        for (const auto& str : this->args) {
            bargv.push_back(const_cast<char*>(str.c_str()));
        }
        bargv.push_back(nullptr);
        execv(bargv[0], bargv.data());

        // TODO: error handling
        // TODO: handle closed terminal
        return;
    }

    // set fd mode to non-blocking read
    if (fcntl(this->master, F_SETFL, O_NONBLOCK) == -1)
        this->throwErrno();
}

void PseudoTTY::writeTTY(const std::string& msg) {
    if (write(this->master, msg.c_str(), msg.length()) == -1)
        this->throwErrno();
}

void PseudoTTY::writeTTY(char c) {
    if (write(this->master, &c, 1) == -1)
        this->throwErrno();
}

std::string PseudoTTY::readTTY() {
    int bcount = -1;
    char buf[128];

    std::stringstream ss;

    while ((bcount = read(this->master, buf, sizeof(buf) - 1)) > 0) {
        buf[bcount] = '\0';
        ss << buf;
    }

    if (bcount == -1 && errno != EWOULDBLOCK) this->throwErrno();

    return ss.str();
}

uint32_t PseudoTTY::readCodepointTTY() {
    uint8_t buf[4];
    uint32_t codepoint = 0;

    if (read(this->master, buf, 1) == -1) {
        if (errno == EWOULDBLOCK) return codepoint;
        this->throwErrno();
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
        throw std::runtime_error("invalid UTF-8 Byte");
    }

    static uint8_t fbMasks[] = { 0b0111'1111, 0b0001'1111, 0b0000'1111, 0b0000'0111 };
    uint8_t fbMask = fbMasks[size];

    // codepoint = (buf[0] & fbMask) << (size * 6);
    codepoint = buf[0] & fbMask;

    if (read(this->master, &buf[1], size) == -1) {
        if (errno == EWOULDBLOCK) throw std::runtime_error("Unexpected end of stream");
        this->throwErrno();
    }

    for (int8_t i = 0; i < size; i++) {
        if ((buf[i] & 0b1100'0000) != 0b1000'0000)
            throw std::runtime_error("invalid UTF-8 Byte");

        codepoint = codepoint << 6;
        codepoint |= buf[i] & 0b0011'1111;
    }

    return codepoint;
}
