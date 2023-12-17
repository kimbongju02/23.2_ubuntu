#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
// 빈 공간의 개수를 나타내는 세마포어
sem_t empty;
// 찬 공간의 개수를 나타내는 세마포어
sem_t full;
// 상호 배제위한 세마포어
sem_t mutex;
// sem_wait(&세마포어) 함수로 대기
// sem_post(&세마포어) 함수로 값 증가

void* producer(void* arg) {
    int item = 1;

    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("Producer produced item %d\n", item);
        buffer[item % BUFFER_SIZE] = item;
        item++;

        sem_post(&mutex);
        sem_post(&full);

        usleep(100000);
    }

    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[0];
        printf("Consumer consumed item %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        usleep(150000);
    }

    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread1, consumer_thread2;

    // 세마포어 초기화
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // 생산자 쓰레드 생성
    pthread_create(&producer_thread, NULL, producer, NULL);

    // 소비자 쓰레드 생성
    pthread_create(&consumer_thread1, NULL, consumer, NULL);
    pthread_create(&consumer_thread2, NULL, consumer, NULL);

    // 쓰레드 종료 대기
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread1, NULL);
    pthread_join(consumer_thread2, NULL);

    // 세마포어 정리
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
