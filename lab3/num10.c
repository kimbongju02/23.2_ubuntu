#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

#define FILE_SIZE 1000
#define SEGMENT_SIZE 1024

struct sembuf acquire = {0, -1, SEM_UNDO};  // semaphore get
struct sembuf release = {0, 1, SEM_UNDO};   // semaphore return

void parent_process(int shmid, int semid, char *source_file, char *destination_file) {
    FILE *source, *destination;
    char *shared_memory;

    // open file
    source = fopen(source_file, "r");
    if (source == NULL) {
        perror("Source file opening failed");
        exit(EXIT_FAILURE);
    }

    destination = fopen(destination_file, "w");
    if (destination == NULL) {
        perror("Destination file opening failed");
        fclose(source);
        exit(EXIT_FAILURE);
    }

    // file data copy to share memory
    while (fread(shared_memory, sizeof(char), SEGMENT_SIZE, source) > 0) {
        semop(semid, &acquire, 1);  // semaphore get
        fwrite(shared_memory, sizeof(char), SEGMENT_SIZE, destination);
        semop(semid, &release, 1);  // semaphore return
    }

    // close file
    fclose(source);
    fclose(destination);

    // delete share memory and semaphore
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
}

void child_process(int shmid, int semid, char *destination_file) {
    FILE *destination;
    char *shared_memory;

    // open file
    destination = fopen(destination_file, "a");
    if (destination == NULL) {
        perror("Destination file opening failed");
        exit(EXIT_FAILURE);
    }

    // add data to share memory
    semop(semid, &acquire, 1);  // semaphore get
    fwrite(shared_memory, sizeof(char), SEGMENT_SIZE, destination);
    semop(semid, &release, 1);  // semaphore return

    // close file
    fclose(destination);

    // delete share memory
    shmdt(shared_memory);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // create share memory
    int shmid = shmget(SHM_KEY, SEGMENT_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // create semaphore 
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }

    // reset semaphore
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl failed");
        exit(EXIT_FAILURE);
    }

    // attachment share memory to process
    char *shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        child_process(shmid, semid, argv[2]);
    } else {
        parent_process(shmid, semid, argv[1], argv[2]);
        wait(NULL);
    }

    return 0;
}
