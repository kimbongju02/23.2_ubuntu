#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int execute_shell_command(const char *command) {
    int result = system(command);

    if (result == -1) {
        perror("command fail");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {

    char command[1000];
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    execute_shell_command(command);

    return 0;
}
