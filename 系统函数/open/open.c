// 使用系统函数 open 来打开文件 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
    int fd = open("a.txt", O_RDONLY);
    printf("File description: %d\n", fd);

    if (fd == -1) {
        perror("a.txt");
    }

    close(fd);

    return 0;
}