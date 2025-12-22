#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main() {
    int fd = open("point.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int32_t x = 10;
    int32_t y = 20;

    write(fd, &x, 4);
    write(fd, &y, 4);

    close(fd);
    return 0;
}
