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