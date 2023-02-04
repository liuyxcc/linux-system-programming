// 使用系统函数 open 来打开文件 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
    // 利用open打开文件
    int fd = open("a.txt", O_RDONLY);

    if (fd == -1) {
        perror("a.txt");
        return -1;
    }

    close(fd);

    // 利用open创建文件
    int fd2 = open("create.txt", O_RDWR | O_CREAT, 0777);

    if (fd2 == -1) {
        perror("create.txt");
        return -1;
    }

    close(fd2);

    return 0;
}