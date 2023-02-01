// 实现 ls -l 命令（也即 ll 
// ll a.txt
// -rw-r--r-- 1 liuyx liuyx 35 Feb  1 16:19 a.txt

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int args, char *argv[]) {
    // 未提供文件名
    if (args < 2) {
        perror("usage: ./ll filename\n");
        return -1;
    }

    struct stat st;

    int ret = stat(argv[1], &st);
    if (ret == -1) {
        perror("error: ");
        return -1;
    }

    // 保存类型和权限的数组
    char type_auth[11] = { 0 };

    // 文件类型
    switch (st.st_mode & S_IFMT) {
    case S_IFSOCK:
        type_auth[0] = 's';
        break;
    case S_IFLNK:
        type_auth[0] = 'l';
        break;
    case S_IFREG:
        type_auth[0] = '-';
        break;
    case S_IFBLK:
        type_auth[0] = 'b';
        break;
    case S_IFCHR:
        type_auth[0] = 'c';
        break;
    case S_IFIFO:
        type_auth[0] = 'p';
        break;
    default:
        type_auth[0] = '?';
        break;
    }

    // user
    type_auth[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    type_auth[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    type_auth[3] = (st.st_mode & S_IXUSR) ? 'r' : '-';

    // group
    type_auth[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    type_auth[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    type_auth[6] = (st.st_mode & S_IXGRP) ? 'r' : '-';

    // other
    type_auth[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    type_auth[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    type_auth[9] = (st.st_mode & S_IXOTH) ? 'r' : '-';

    // links
    int links = st.st_nlink;

    // fileuser
    char *fileuser = getpwuid(st.st_gid)->pw_name;

    // filegroup
    char *filegroup = getgrgid(st.st_gid)->gr_name;

    // size
    long size = st.st_size;

    // time
    // 由于通过ctime处理得到的字符串结尾会有换行符，故需要处理一下
    char *t = ctime(&st.st_mtime);
    char time[512] = { 0 };
    strncpy(time, t, strlen(t) - 1);

    char buf[1024] = { 0 };
    sprintf(buf, "%s %d %s %s %ld %s %s", type_auth, links, fileuser, filegroup, size, time, argv[1]);
    printf("%s\n", buf);

    return 0;
}