#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // create child process
    pid_t child_pid = fork();

    // fail child process
    if (child_pid < 0) {
        perror("Fail Fork");
        exit(EXIT_FAILURE);
    }

    // parent process block
    if (child_pid > 0) {
        printf("parent process (PID: %d)\n", getpid());
        printf("child process created (PID: %d)\n", child_pid);

        wait(NULL);
        printf("child process exit\n");
    }
    // chlid process block
    else {
        printf("chlid process (PID: %d)\n", getpid());
        
        printf("chlid process exit\n");
    }

    return 0;
}
