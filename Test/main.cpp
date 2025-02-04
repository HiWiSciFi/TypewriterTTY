#include <fcntl.h>
#include <iostream>
#include <pty.h>
#include <unistd.h>

#include <utmp.h>

int runSingle();
int runFork();

int main(int argc, char** argv) {
    return runFork();
}

int runSingle() {
    int master, slave;
    if (openpty(&master, &slave, NULL, NULL, NULL) == -1) {
        perror("ERROR: openpty");
        return -1;
    }

    if (login_tty(slave) == -1) {
        perror("ERROR: login_tty");
        return -1;
    }
    return 0;
}

int runFork() {
    int master;
    // TODO: populate terminal and window options
    termios termp = { };
    winsize winp = {
        .ws_row = 1,
        .ws_col = 200,
        .ws_xpixel = 1,
        .ws_ypixel = 200
    };
    pid_t childPid = forkpty(&master, NULL, NULL, &winp);

    if (childPid == -1) {
        perror("ERROR: forkpty");
        return -1;
    }

    if (childPid == 0) {
        // start slave pty
        while (true) execl("/bin/bash", "bash", NULL);
        return 0;
    }

    // set fd mode to non blocking read
    if (fcntl(master, F_SETFL, O_NONBLOCK) == -1) {
        perror("ERROR: fcntl");
        return -1;
    }

    // start master pty
    int count = 0;
    while (true) {
        if (write(master, "ls -la\n", 7) == -1) perror("ERROR: write");
        sleep(1);

        int nb_read = -1;
        char buf[128];

        while ((nb_read = read(master, buf, sizeof(buf) - 1)) > 0) {
            buf[nb_read] = '\0';
            std::cout << buf << std::flush;
        }

        if (nb_read == -1 && errno != EWOULDBLOCK) perror("ERROR: read");
    }
    return 0;
}
