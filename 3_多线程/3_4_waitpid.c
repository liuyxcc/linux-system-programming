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
            sleep(2);

            int status;

            // 当 waitpid 函数的第三个参数为 WNOHANG 时可以不阻塞父进程的运行
            int ret = waitpid(-1, &status, WNOHANG);

            // waitpid(): on success, returns the process ID of the child whose state has changed; if WNOHANG was specified and one or more child(ren) specified by pid exist, but have not yet changed state, then 0 is returned.  On error, -1 is returned.
            if (ret == -1) {                // 为 -1 时说明已经没有可回收的子进程了
                break;
            } else if (ret == 0) {          // 为 0 说明还有子进程
                continue;
            } else if (ret > 0) {           // 为 大于0 的数，即返回了子进程的的pid，且子进程的的状态已改变
                if (WIFEXITED(status)) {    // 子进程是正常退出
                    printf("Exit normally.\n");
                }
                if (WIFSIGNALED(status)) {  // 子进程是通过信号量强制退出，例如 ctrl c
                    printf("Killed by signal %d.\n", status);
                }

                printf("Child is died, it's pid = %d\n", ret);
            }
        }
    } else if (pid == 0) {
        while (1) {
            printf("Child, pid = %d\n", getpid());
            sleep(2);
        }
    }

    return 0;
}