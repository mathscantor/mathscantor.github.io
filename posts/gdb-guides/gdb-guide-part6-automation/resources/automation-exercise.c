#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <linux/types.h>
#include <sys/select.h>
#include <sched.h>

void watchdog(pid_t watched_pid, int read_fd) {
    time_t last_heartbeat = time(NULL);
    char buffer[10];

    while (1) {
        fd_set fds;
        struct timeval timeout;
        FD_ZERO(&fds);
        FD_SET(read_fd, &fds);
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        int ret = select(read_fd + 1, &fds, NULL, NULL, &timeout);
        if (ret > 0 && read(read_fd, buffer, sizeof(buffer)) > 0) {
            last_heartbeat = time(NULL);
        } else {
            if (time(NULL) - last_heartbeat > 2) {
                printf("No heartbeat detected. Killing watched process...\n");
                kill(watched_pid, SIGKILL);
                exit(1);
            }
        }
    }
}

void watched_process(int write_fd) {
    while (1) {
        printf("Watched process (pid: %d) is running...\n", getpid());
        write(write_fd, "alive", 5);
        sleep(1);
    }
}

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (pid == 0) { // Watched process
        close(pipefd[0]); // Close read end
        watched_process(pipefd[1]);
    } else { // Watchdog process
        close(pipefd[1]); // Close write end
        watchdog(pid, pipefd[0]);
    }
    return 0;
}