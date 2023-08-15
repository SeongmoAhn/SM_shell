// my_cat.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096

void cat(int argc, char **argv) {
    char buf[BUFFER_SIZE];

    if (argc == 1) {
        fprintf(stderr, "Usage : %s {FILENAME}+\n", argv[0]);
        fprintf(stderr, "        %s {FILENAME}+ > <OUTPUT_FILENAME>\n", argv[0]);
        exit(1);
    }
    else if (argc == 2) {
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, "open error for %s\n", argv[1]);
            exit(1);
        }

        while (1) {
            int length;
            
            if ((length = read(fd, buf, BUFFER_SIZE)) < 0) {
                fprintf(stderr, "read error\n");
                exit(1);
            }
            else if (length == 0) break;

            write(STDOUT_FILENO, buf, length);
        }
    }
}
