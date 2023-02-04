/**
 *  #include <unistd.h>
 *  #include <fcntl.h>
 *
 *  int fcntl(int fd, int cmd, ...);
 *
 *  可用于复制文件描述符或修改其flag
 *
 *  - fd：表示需要操作的文件描述符
 *  - cmd：表示对文件描述符进行如何操作
 *      - F_DUPFD：复制文件描述符fd并返回
 *      - F_GETFL：获取描述符为fd的文件状态flag并返回（flag与open函数中的参数是一样的东西）
 *      - F_SETFL：设置描述符为fd的flag
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // 打开1.txt并获取其文件描述符
    int fd = open("1.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // 利用fcntl为文件操作新增尾部添加权限
    int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag | O_APPEND);

    // 这时就可以从文件尾写入内容了
    char *str = "1111";
    write(fd, str, strlen(str));

    return 0;
}