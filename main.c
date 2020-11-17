#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
    int fd = open("/dev/random", O_RDONLY);
    int arr[10]; int check[10]; int i;

    if(fd == -1) {
        printf("Error: %d %s\n",errno, strerror(errno));
        return -1;
    }

    printf("Generating Random Numbers: \n");
    for(i = 0; i < sizeof(arr)/sizeof(int); i++){
        int* p = arr + i;
        read(fd, p, 4);
    }
    close(fd);

    for(i = 0; i < sizeof(arr)/sizeof(int); i++){
        printf("%d\n", arr[i]);
    }

    fd = open("./out.txt", O_WRONLY | O_CREAT, 744);
    if(fd == -1) {
        printf("Error: %d  %s\n",errno, strerror(errno));
        return -1;
    }

    printf("Writing to file\n");
    write(fd, arr + 0, 4*10);
    close(fd);

    fd = open("./out.txt", O_RDONLY);
    if(fd == -1) {
        printf("Error: %d  %s\n",errno, strerror(errno));
        return -1;
    }

    printf("Reading from file\n");
    read(fd, check , 4*10);
    close(fd);

    for(i = 0; i < sizeof(arr)/sizeof(int); i++){
        printf("%d\n", check[i]);
    }

    return 0;
}
