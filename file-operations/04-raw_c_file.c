#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int fd = open("data.bin", O_RDONLY);
    if(fd<0){
        perror("open");
        return 1;
    }

    unsigned char buf[4];
    size_t n = read(fd, buf, 4);
    if(n<0){
        perror("Read");
        return 1;
    }

    close(fd);

    printf("Bytes Read : ");
    for(int i=0; i<n; i++){
        printf("%02X", buf[i]);
    }
    printf("\n");

    int value = *(int*)buf;
    printf("Interpreted as int: %d\n", value);

    return 0;
}