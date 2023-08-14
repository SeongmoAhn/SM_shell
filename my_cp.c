// my_cp.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096
#define PATH_MAX 4096

void cp(int argc, char **argv) {
    int fd1, fd2;
    char buf[BUFFER_SIZE]; int length;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <FILENAME1> <FILENAME2>\n", argv[0]);
        exit(1);
    }

    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "open error for %s\n", argv[2]);
        exit(1);
    }

    while (1) {
        if ((length = read(fd1, buf, BUFFER_SIZE)) < 0) {
            fprintf(stderr, "read error\n");
            exit(1);
        }
        else if (length == 0) break;

        write(fd2, buf, length);
    }

    close(fd1);
    close(fd2);
    exit(0);
}
