/**
 *  #include <unistd.h>
 *  ssize_t read(int fd, void *buf, size_t count);
 *  ssize_t write(int fd, const void *buf, size_t count);
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int src_fd = open("source.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("open");
        return -1;
    }

    int copy_fd = open("copy.txt", O_WRONLY | O_CREAT, 0664);
    if (copy_fd == -1) {
        perror("open");
        return -1;
    }

    char buf[1024] = { 0 };
    int len = 0;
    while ((len = read(src_fd, buf, sizeof(buf))) > 0) {
        write(copy_fd, buf, len);
    }

    close(copy_fd);
    close(src_fd);

    return 0;
}