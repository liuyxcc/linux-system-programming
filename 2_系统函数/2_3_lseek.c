/*
    头文件
    #include <sys/type.h>
    #include <unistd.h>

    函数原型
    off_t lseek(int fd, off_t offset, int whence);

    参数
    - `fd`：文件描述符
    - `offset`：偏移量
    - `whence`：设置偏移量
        - `SEEK_SET`：文件头部 + 第二个参数offset的值
        - `SEEK_CUR`：当前位置 + offset的值
        - `SEEK_END`：文件大小 + offset的值

    作用
    1. 移动文件指针到文件头
        ```c
        lseek(fd, 0, SEEK_SET);
        ```
    2. 获取当前文件指针的位置
        ```c
        lseek(fd, 0, SEEK_CUR);
        ```
    3. 获取文件长度
        ```c
        lseek(fd, 0, SEEK_END);
        ```
    4. 扩展文件长度，假设当前文件为10b，需要拓展100b，则
        ```c
        lseek(fd, 100, SEEK_END);
        write(fd, " ", 1); // 利用write写入才能实现真正的扩展
        ```
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd = open("a.txt", O_RDWR);
    if (fd == -1) {
        perror("a.txt");
    }

    lseek(fd, 100, SEEK_END);
    write(fd, " ", 1);

    close(fd);

    return 0;
}