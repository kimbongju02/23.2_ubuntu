#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mHeader.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("사용법: %s [add|sub|mul|div] 정수1 정수2\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);

    if (strcmp(operation, "add") == 0) {
        int result = mAdd(x, y);
        printf("덧셈 결과: %d\n", result);
    } else if (strcmp(operation, "sub") == 0) {
        int result = mSub(x, y);
        printf("뺄셈 결과: %d\n", result);
    } else if (strcmp(operation, "mul") == 0) {
        int result = mMul(x, y);
        printf("곱셈 결과: %d\n", result);
    } else if (strcmp(operation, "div") == 0) {
        int result = mDiv(x, y);
        printf("나눗셈 결과: %d\n", result);
    } else {
        printf("잘못된 연산자 입력: %s\n", operation);
        return 1;
    }

    return 0;
}

