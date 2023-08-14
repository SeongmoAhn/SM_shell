#include <stdio.h>

void help() {
    printf("Usage : \n");
    printf("  > help\n");
    printf("  > exit\n");
    printf("  > clear\n");
    printf("  > pwd\n");
    printf("  > ls [OPTION]\n");
    printf("    -a : include directory entries whose names begin with a '.'\n");
    printf("    -l : print directory entries by list format\n");
    printf("  > vi[m] [FILENAME]\n");
    printf("  > cd [PATH]\n");
    printf("  > cp <FILENAME1> <FILENAME2>\n");
    printf("  > cat {FILENAME}+\n");
    printf("    cat {FILENAME1}+ > <OUTPUT_FILENAME>\n");

    printf("\n");
}
