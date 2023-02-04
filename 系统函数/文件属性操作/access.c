#include <stdio.h>
#include <unistd.h>

int main() {
    // 判断文件是否存在
    if (access("./README.md", F_OK) == 0) {
        printf("file exist.\n");
    }

    return 0;
}