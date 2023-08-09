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

void lsExec() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        execl(execName, "ls", (char *)0);
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

    while (1) {
        printf("SM_shell > ");
        
        fgets(input, STR_MAX, stdin);
        input[strlen(input) - 1] = '\0';

        if (!strcmp(input, commandList[0])) { // exit
            fprintf(stdout, "* SM_shell exit... *\n");
            exit(0);
        } else if (!strcmp(input, commandList[1])) { // help
            command = CMD_HELP;
        } else if (!strcmp(input, commandList[2])) {
            printf("%s\n\n", execPath);
            command = CMD_PWD;
            continue;
        } else if (!strcmp(input, commandList[3])) {
            command = CMD_LS;
        }
        else {
            command = NOT_CMD;
        }

        if (command & CMD_HELP || command == NOT_CMD) {
            helpExec();
        } else if (command & CMD_LS) {
            lsExec();
        }
    }
}

int main(int argc, char **argv) {
    init();

    strcpy(execName, argv[0]);

    if (!strcmp(argv[0], "help")) {
        help();
    } else if(!strcmp(argv[0], "ls")) {
        ls();
    }
    else {
        prompt();
    }

    exit(0);
}
