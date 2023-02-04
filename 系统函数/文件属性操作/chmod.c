#include <sys/stat.h>
#include <stdio.h>

int main() {
    if (chmod("./README.md", 0644) == -1) {
        perror("chmod");
        return -1;
    }
    return 0;
}