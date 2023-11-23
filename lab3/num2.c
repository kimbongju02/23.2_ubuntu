#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    // open current dir
    DIR *directory = opendir(".");

    // fail open dir
    if (directory == NULL) {
        perror("Fail Open Dir");
        exit(EXIT_FAILURE);
    }

    // read dir
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // close dir
    closedir(directory);

    return 0;
}
