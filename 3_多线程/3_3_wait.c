#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // 创建五个子进程
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (pid > 0) {
        while (1) {
            printf("Parent, pid = %d\n", getpid());

            int status;
            // 调用wait函数会阻塞父进程，直到子进程终止
            int ret = wait(&status);
            // 为 -1 时说明已经没有可回收的子进程了
            if (ret == -1) {
                break;
            }

            // 子进程是正常退出
            if (WIFEXITED(status)) {
                printf("Exit normally.\n");
            }
            // 子进程是通过信号量强制退出，例如 ctrl c
            if (WIFSIGNALED(status)) {
                printf("Killed by signal %d.\n", status);
            }

            printf("Child is died, it's pid = %d\n", ret);

            sleep(2);
        }
    } else if (pid == 0) {
        while (1) {
            printf("Child, pid = %d\n", getpid());
            sleep(2);
        }
    }

    return 0;
}