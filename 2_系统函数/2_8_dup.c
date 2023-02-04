/**
 *  #include <unistd.h>
 *
 *  int dup(int oldfd); // 复制一个文件描述符
 *  int dup2(int oldfd, int newfd); // 将newfd文件描述符重定向到oldfd
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // 创建一个 1.txt 的文件，其文件描述符为 fd
    int fd = open("1.txt", O_RDWR | O_CREAT);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // 利用 dup 复制文件描述符，并利用复制的文件 fd1 描述符去进行写入操作，最终将 str 写入 1.txt
    int fd1 = dup(fd);
    char *str = "hello, dup";
    int len = write(fd1, str, strlen(str));
    if (len == -1) {
        perror("write");
        return -1;
    }

    // 这里执行 close(fd) 貌似会报错？
    close(fd1);

    return 0;
}