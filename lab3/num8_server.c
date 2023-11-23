#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 256
#define SERVER_KEY 1234

struct message {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main() {
    int msgid = msgget(SERVER_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget fail");
        exit(EXIT_FAILURE);
    }

    printf("start chatting\n");

    struct message msg;

    while (1) {
        // receive massage from massage queue
        if (msgrcv(msgid, &msg, MAX_MESSAGE_SIZE, 1, 0) == -1) {
            perror("msgrcv fail");
            exit(EXIT_FAILURE);
        }

        printf("client: %s", msg.mtext);

        if (strcmp(msg.mtext, "exit\n") == 0) {
            printf("end chatting\n");
            break;
        }
    }

    // delete massage queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl fail");
        exit(EXIT_FAILURE);
    }

    return 0;
}
