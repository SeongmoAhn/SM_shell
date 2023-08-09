// my_header.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define STR_MAX 4096
#define PATH_MAX 4096

#define NOT_CMD  0b0000000
#define CMD_EXIT 0b0000001
#define CMD_HELP 0b0000010
#define CMD_PWD  0b0000100
#define CMD_LS   0b0001000

char execPath[PATH_MAX];
char homePath[PATH_MAX];
char execName[PATH_MAX];

char *commandList[4] = {
    "exit",
    "help",
    "pwd",
    "ls"
};

void help();
void ls();
