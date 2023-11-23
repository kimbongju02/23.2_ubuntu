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
    int msgid = msgget(SERVER_KEY, 0666);
    if (msgid == -1) {
        perror("msgget fail");
        exit(EXIT_FAILURE);
    }

    printf("start chatting\n");

    struct message msg;

    while (1) {
        fgets(msg.mtext, MAX_MESSAGE_SIZE, stdin);
        msg.mtype = 1; // massage type

        // receive massage to massage queue
        if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            perror("msgsnd 실패");
            exit(EXIT_FAILURE);
        }

        if (strcmp(msg.mtext, "exit\n") == 0) {
            printf("채팅 클라이언트 종료\n");
            break;
        }
    }

    return 0;
}
