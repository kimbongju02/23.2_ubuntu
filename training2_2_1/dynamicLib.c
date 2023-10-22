#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dlfcn.h>

int main(int argc, char *argv[]) {
	void *handle = dlopen("./math_op.so", RTLD_LAZY);

	if(!handle){
		fprintf(stderr, "라이브러리 불러오기 불가: %s\n", dlerror());
		return 1;
	}
    	if (argc != 4) {
        	printf("사용법: %s [add|sub|mul|div] 정수1 정수2\n", argv[0]);
	        return 1;
	}

	int (*add_func)(int, int) = dlsym(handle,"mAdd");
	int (*sub_func)(int, int) = dlsym(handle, "mSub");
	int (*mul_func)(int, int) = dlsym(handle, "mMul");
	int (*div_func)(int, int) = dlsym(handle, "mDiv");

    	char *operation = argv[1];
    	int x = atoi(argv[2]);
    	int y = atoi(argv[3]);

    	if (strcmp(operation, "add") == 0) {
        	int result = add_func(x, y);
        	printf("덧셈 결과: %d\n", result);
    	} else if (strcmp(operation, "sub") == 0) {
        	int result = sub_func(x, y);
        	printf("뺄셈 결과: %d\n", result);
    	} else if (strcmp(operation, "mul") == 0) {
        	int result = mul_func(x, y);
        	printf("곱셈 결과: %d\n", result);
    	} else if (strcmp(operation, "div") == 0) {
        	int result = div_func(x, y);
        	printf("나눗셈 결과: %d\n", result);
    	} else {
        	printf("잘못된 연산자 입력: %s\n", operation);
        	return 1;
    	}

    	return 0;
}
