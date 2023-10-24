#include <stdio.h>
#include <stdlib.h>

// 조건을 문자열화하는 매크로
#define STR(x) #x

void my_assert(int condition) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: " STR(condition) "\n");
        abort(); // 프로그램 중단
    }
}

int main() {
    int num = 120; // 예시로 120을 사용

    my_assert((num >= 0) && (num <= 100));

    // 만약 조건이 만족하지 않으면 프로그램이 여기까지 도달하지 않음
    printf("프로그램 계속 실행됨\n");

    return 0;
}

