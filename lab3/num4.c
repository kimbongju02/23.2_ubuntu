#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1000

int main() {
    char sentence[MAX_LENGTH] = "Hello, my name is kimbongju. I live in South Korea. I am attending Dongui University.";
    char user_input[MAX_LENGTH];

    // start time
    time_t start_time = time(NULL);
    printf("input sentence: \n%s\n", sentence);
    // user input
    printf("start: \n");
    fgets(user_input, MAX_LENGTH, stdin);

    // end time
    time_t end_time = time(NULL);

    // 개행 문자 제거
    user_input[strcspn(user_input, "\n")] = '\0';

    // 정확도 계산
    int correct = 0;
    int wrong = 0;

    for (int i = 0; i < strlen(sentence) && i < strlen(user_input); i++) {
        if (sentence[i] == user_input[i]) {
            correct++;
        } else {
            wrong++;
        }
    }

    // elapsed_seconds
    double elapsed_seconds = difftime(end_time, start_time);

    // average_typing_speed
    double average_typing_speed = (correct + wrong) / elapsed_seconds * 60;

    printf("wrong typing: %d\n", wrong);
    printf("average_typing_speed: %.2f\n", average_typing_speed);

    return 0;
}
