// main.c
#include <stdio.h>

extern int add(int a, int b);
extern int subtract(int a, int b);
extern int multiply(int a, int b);
extern int divide(int a, int b);

int main() {
    int a = 10, b = 5;
    int result;
    
    result = add(a, b);
    printf("덧셈 결과: %d\n", result);
    
    result = subtract(a, b);
    printf("뺄셈 결과: %d\n", result);
    
    result = multiply(a, b);
    printf("곱셈 결과: %d\n", result);
    
    result = divide(a, b);
    printf("나눗셈 결과: %d\n", result);
    
    return 0;
}

