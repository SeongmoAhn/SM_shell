// SM_shell.c
#include "my_header.h"

void helpExec() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        execl(execName, "help", (char *)0);
        exit(0);
    }
    else {
        pid = wait(NULL);
    }
}

void lsExec(char **argList) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        execv(execName, argList);
        exit(0);
    }
    else {
        pid = wait(NULL);
    }
}

void init() {
    getcwd(execPath, PATH_MAX);
    sprintf(homePath, "%s", getenv("HOME"));
}

void prompt() {
    char input[STR_MAX];
    int command;
    int argCnt;
    char **argList = NULL;

    while (1) {
        printf("SM_shell > ");
        
        fgets(input, STR_MAX, stdin);
        input[strlen(input) - 1] = '\0';
        if ((argList = divideString(input, &argCnt, " \t")) == NULL) {
            continue;
        }

        if (!strcmp(input, "clear")) {
            system("clear");
            continue;
        }

        if (!strcmp(input, commandList[0])) { // exit
            fprintf(stdout, "* SM_shell exit... *\n");
            exit(0);
        } else if (!strcmp(argList[0], commandList[1])) { // help
            command = CMD_HELP;
        } else if (!strcmp(argList[0], commandList[2])) {
            printf("%s\n\n", execPath);
            command = CMD_PWD;
            continue;
        } else if (!strcmp(argList[0], commandList[3])) {
            command = CMD_LS;
        }
        else {
            command = NOT_CMD;
        }

        if (command & CMD_HELP || command == NOT_CMD) {
            helpExec();
        } else if (command & CMD_LS) {
            lsExec(argList);
        }
    }
}

int main(int argc, char **argv) {
    init();

    strcpy(execName, argv[0]);

    if (!strcmp(argv[0], "help")) {
        help();
    } else if(!strcmp(argv[0], "ls")) {
        ls(argc, argv);
    }
    else {
        prompt();
    }

    exit(0);
}
