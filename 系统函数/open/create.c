#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    int fd = open("create.txt", O_RDWR | O_CREAT, 0777);

    if (fd == -1) {
        perror("create.txt");
    }

    close(fd);

    return 0;
}