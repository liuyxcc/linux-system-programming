#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("I'm child1's parent process\n");
    } else if (pid == 0) {
        // execl 第一个参数为路径， 第二个为文件名，之后为可执行程序的参数，最后以NULL结尾
        execl("/bin/ls", "ls", "-l", NULL);

        // execlp 第一个参数为 可执行程序名 （将会去环境变量查找，如果没有则执行失败，并设置errno），第二个开始为 参数列表 ，最后也以 NULL 结尾
        // execlp("ps", "aux", NULL);
        perror("execl");
    }

    return 0;
}