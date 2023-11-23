#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void child_process_handler(int signal) {
    if (signal == SIGUSR1) {
        printf("chlid process: SIGUSR1 signal reception\n");
    }
}

int main() {
    // signal handler registe
    signal(SIGUSR1, child_process_handler);

    pid_t child_pid = fork();

    // fail call fork
    if (child_pid < 0) {
        perror("fail fork");
        exit(EXIT_FAILURE);
    }

    // parent process block
    if (child_pid > 0) {
        printf("parent process (PID: %d)\n", getpid());
        
        sleep(1);
        kill(child_pid, SIGUSR1);
    }
    // child process block
    else {
        
        while (1) {
            sleep(1);
        }
    }

    return 0;
}
