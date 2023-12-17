#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    // TCP 소켓 생성
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind 함수로 소켓에 주소 할당
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // listen 함수로 클라이언트 연결 대기
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening on socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server on port %d...\n", PORT);

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        /*   accept(클라이언트의 연결을 기다리고 있는 서버 소켓의 파일 디스크립터, 
                    클라이언트의 정보를 저장할 구조체, 
                    클라이언트 주소 구조체의 크기를 나타내는 변수의 포인터)
        */
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        printf("Accepted connection from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        char buffer[BUFFER_SIZE];
        ssize_t bytesRead;

        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytesRead] = '\0';
            printf("Received message from client: %s\n", buffer);

            // 에코 메시지를 클라이언트에게 다시 보냄
            send(clientSocket, buffer, bytesRead, 0);
        }

        close(clientSocket);
        printf("Connection with %s:%d closed\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    }

    close(serverSocket);

    return 0;
}
