/**
 *  #include <stdio.h>
 *  int rename(const char *oldpath, const char *newpath);
 *
 *  #include <unistd.h>
 *  int chdir(const char *path);
 *  char *getcwd(char *buf, size_t size);
 *
 *  #include <sys/types.h>
 *  #include <sys/stat.h>
 *  int mkdir(const char *pathname, mode_t mode);
 *  int rmdir(const char *pathname); // 只能删除空目录
 *
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {

    // 创建目录，若已存在则返回-1，成功则返回0
    if (mkdir("./dir", 0777) == -1) {
        printf("文件已存在\n");
    }

    // 修改目录名
    if (rename("./dir", "./newdir") == -1) {
        perror("rename");
    }

    // 改变当前工作目录（执行该代码前请确保存在 “chdir” 目录）
    if (chdir("./chdir") != -1) {
        char buf[256];
        getcwd(buf, sizeof(buf));
        printf("当前工作目录：%s\n", buf);
    } else {
        perror("chdir");
    }

    return 0;
}
