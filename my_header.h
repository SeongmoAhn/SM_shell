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
