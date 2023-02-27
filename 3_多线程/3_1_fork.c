#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // 当 pid > 0 时，说明这是在 父 进程中，并且此时的 pid 即为子进程的 id
    // 当 pid == 0 时，说明这是在 子 进程中，此时可通过 getpid 来获取子进程的id
    // 当 pid == -1 时，说明创建子进程失败，此时会将 错误信息 “放入” errno 全局变量中
    pid_t pid = fork();
    int num = 100;

    if (pid > 0) {
        // 这是父进程
        printf("son's pid = %d\n", pid);
        num += 10;
        printf("dad process: num = %d\n", num);
        printf("num's addr = %p\n", &num);
    } else if (pid == 0) {
        // 这是子进程
        printf("son is created, it's pid = %d\n", getpid());
        num -= 10;
        printf("son process: num = %d\n", num);
        printf("num's addr = %p\n", &num);
    }

    printf("together, num = %d\n", num);
    return 0;
}

/*
执行后num的address一样，按理来说，，num不应该copy了一份吗，这是为什么呢？

num 相对于两个进程的逻辑地址一样 ，但是映射在物理空间就不一样了（虚拟空间每个进程都是共享的,映射到物理空间就可能会不一样）。

不同的进程访问同样的逻辑地址而对应的物理地址不同，是由于各自页表的不同。

linux系统下每个进程都拥有自己的页表，父进程fork出新的子进程时，子进程拷贝一份父进程的页表，且父子进程将页表状态修改为写保护。当父进程或子进程发生写操作时将会发生缺页异常，缺页异常处理函数将会为子进程分配新的物理地址。
*/
