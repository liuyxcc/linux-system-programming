#include <stdio.h>
#include <unistd.h>

int main() {
    // 判断文件是否存在
    if (access("./a.txt", F_OK) == 0) {
        printf("file exist.\n");
    }

    // 修改文件权限。
    if (chmod("./a.txt", 0644) == -1) {
        perror("chmod");
    }

    // 对文件进行缩减或扩展。
    if (truncate("./a.txt", 1000) == -1) {
        perror("truncate");
    }
    return 0;
}