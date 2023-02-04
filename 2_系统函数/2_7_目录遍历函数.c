/**
 *  #include <sys/types.h>
 *  #include <dirent.h>
 *  DIR *opendir(const char *name);
 *
 *  #include <dirent.h>
 *  struct dirent *readdir(DIR *dirp);
 *
 *  #include <sys/types.h>
 *  #include <dirent.h>
 *  int closedir(DIR *dirp);
 *
 *  利用上述函数实现查找一个目录下普通文件的个数
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GetFileNum(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(0);
    }

    int total = 0;

    struct dirent *rd = NULL;
    while ((rd = readdir(dir)) != NULL) {
        // 获取当前位置的名称
        char *dname = rd->d_name;

        // 如果是“.”或“..”，跳过
        if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
            continue;

        // 若是一个目录，递归处理，注意目录名的处理
        // 若是一个普通文件，total += 1
        if (rd->d_type == DT_DIR) {
            char nextdir[256];
            sprintf(nextdir, "%s/%s", path, dname);
            total += GetFileNum(nextdir);
        } else if (rd->d_type == DT_REG) {
            total += 1;
        }
    }

    closedir(dir);

    return total;

}

int main(int args, char *argv[]) {
    if (args != 2) {
        printf("%s: 参数个数有误！\n", argv[0]);
        return -1;
    }

    printf("普通文件个数为：%d\n", GetFileNum(argv[1]));

    return 0;
}