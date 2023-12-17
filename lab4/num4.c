#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 256
#define NUM_THREAD 3

char messageQueue[MAX_MESSAGE_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int activeChildThreads = NUM_THREAD;

// 각 쓰레드에서 실행되는 함수
void* childThreadFunction(void* arg) {
    char* message = (char*)arg;

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex); // 뮤텍스 잠금
        if(strcmp(message, "1") == 0 && i == 2){
            strcpy(messageQueue, "Thread 3 call massage to parent");
            printf("Thread '%s'의 '%d'번째\n", message, i + 1);
            pthread_cond_signal(&cond);
        }else{
            printf("Thread '%s'의 '%d'번째\n", message, i + 1);
        }
        pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
        usleep(1000000);
    }
    pthread_mutex_lock(&mutex);
    --activeChildThreads;
    printf("activeChildThreads : %d\n", activeChildThreads);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* parentThread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // 모든 자식 스레드가 종료되면 부모 스레드 종료
        if (activeChildThreads == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // 자식 스레드가 메시지를 보낼 때까지 대기
        while (messageQueue[0] == '\0') {
            pthread_cond_wait(&cond, &mutex);
        }

        // 메시지 큐에서 메시지를 꺼내고 출력
        char message[MAX_MESSAGE_SIZE];
        strcpy(message, messageQueue);
        messageQueue[0] = '\0';

        // 부모 스레드에서 메시지 처리
        printf("Received message from child: %s\n", message);

        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

int main() {
    pthread_t tid[NUM_THREAD];
    pthread_t parent_thread;
    pthread_create(&parent_thread, NULL, parentThread, NULL);

    // 자식 스레드 생성 및 시작
    for (int i = 0; i < NUM_THREAD; ++i) {
        char* message = (char*)malloc(MAX_MESSAGE_SIZE);
        sprintf(message, "%d",  i);
        if (pthread_create(&tid[i], NULL, childThreadFunction, (void*)message) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // 모든 자식 스레드의 종료를 기다림
    for (int i = 0; i < NUM_THREAD; ++i) {
        pthread_join(tid[i], NULL);
    }

    // 부모 스레드의 종료를 기다림
    pthread_join(parent_thread, NULL);

    return 0;
}
