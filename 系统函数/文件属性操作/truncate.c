#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    if (truncate("./README", 1000) == -1) {
        perror("truncate");
        return -1;
    }
    return 0;
}