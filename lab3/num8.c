#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t child_pid;

    // create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // child process block
        close(pipefd[1]);

        char buffer[100];
        ssize_t num_bytes = read(pipefd[0], buffer, sizeof(buffer));

        close(pipefd[0]);

        printf("received message: %.*s\n", (int)num_bytes, buffer);
    } else { // parent process block
        close(pipefd[0]);

        const char *message = "Interprocess Communication";
        write(pipefd[1], message, strlen(message));

        close(pipefd[1]);

        wait(NULL);
    }

    return 0;
}
