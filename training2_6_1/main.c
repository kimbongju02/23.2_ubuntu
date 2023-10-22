#include <stdio.h>
#include <stdlib.h>

#define STR(x)

void my_assert(int condition, const char *message) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: %s", message);
        abort();
    }
}

void foo(int num) {
    int condition = ((num >= 0) && (num <= 100));
    const char *condition_string = STR((num >= 0) && (num <= 100));
    my_assert(condition, condition_string);
    printf("foo: num = %d\n", num);
}

int main(int argc, char *argv[]) {
    int num;

    if (argc < 2) {
        fprintf(stderr, "Usage: assert_test aNumber\n(0 <= aNumber <= 100)\n");
        exit(1);
    }

    num = atoi(argv[1]);
    foo(num);

    return 1;
}
