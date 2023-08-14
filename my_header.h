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
#define CMD_VIM  0b0010000
#define CMD_CD   0b0100000
#define CMD_CP   0b1000000

char execPath[PATH_MAX];
char homePath[PATH_MAX];
char *codePath = "/Users/asm/code/sysp/makeShell/";
char execName[PATH_MAX];

char *commandList[8] = {
    "exit",
    "help",
    "pwd",
    "ls",
    "vim",
    "vi",
    "cd",
    "cp"
};

void help();
void ls(int, char **);
void vim(int, char **);
void cp(int, char **);

char **divideString(char *str, int *cnt, char *del) {
    *cnt = 0;
    char *tempList[100] = {(char *)NULL, };
    char **retList = (char **)malloc(sizeof(char *) * (*cnt + 1));
    char *token = NULL;

    token = strtok(str, del);
    if (token == NULL) return NULL;
    while (token != NULL) {
        tempList[(*cnt)++] = token;
        token = strtok(NULL, del);
    }

    for (int i = 0; i < *cnt; i++) {
         retList[i] = tempList[i];
    }
    return retList;
}
