#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 각 쓰레드에서 실행되는 함수
void* printMessage(void* args) {
    char* message = (char*)args;
    
    for (int i = 0; i < 5; ++i) {
        printf("%s의 %d번째\n", message, i+1);
        usleep(4000000);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // &thread1 - 새로 생성되는 쓰레드의 식별자를 저장할 포인터 
    // 생성된 쓰레드를 식별, 조작 가능
    if (pthread_create(&thread1, NULL, printMessage, (void*)"Thread 1") != 0) {
        perror("Error creating thread 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, printMessage, (void*)"Thread 2") != 0) {
        perror("Error creating thread 2");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; ++i) {
        printf("Main Thread\n");
        usleep(200000);
    }

    if (pthread_join(thread1, NULL) != 0) {
        perror("Error joining thread 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Error joining thread 2");
        exit(EXIT_FAILURE);
    }

    return 0;
}
