#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void listFilesRecursively(const char *basePath) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // fail open dir
    if (!dir) {
        perror("Fail Open Dir");
        return;
    }

    // dir, file list
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            printf("%s/%s\n", basePath, dp->d_name);

            // dir recursion
            if (dp->d_type == DT_DIR) {
                sprintf(path, "%s/%s", basePath, dp->d_name);
                listFilesRecursively(path);
            }
        }
    }

    closedir(dir);
}

int main() {
    char basePath[100] = "/home/linux/23.2_ubuntu/training2";
    listFilesRecursively(basePath);

    return 0;
}
