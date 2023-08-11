// my_ls.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define OPT_A 0b00001
#define OPT_L 0b00010
#define OPT_I 0b00100

typedef struct _node {
    char *fileName;
    struct _node *next;
} Node;

Node *head = NULL;
int maxLength = -1;
int terminalWidth = 0;

void addNode(Node *newNode) {
    if (head == NULL) {
        head = newNode;
    }
    else {
        Node *cur = head;

        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

void deleteNode() {
    while (head != NULL) {
        Node *del = head;
        head = head->next;
        free(del);
    }
}

Node *createNode(char *fname) {
    Node *ret = (Node *)malloc(sizeof(Node));
    ret->next = NULL;
    ret->fileName = fname;

    return ret;
}

void makeList() {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(".")) == NULL) {
        fprintf(stderr, "opendir error\n");
        exit(1);
    }

    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &statbuf) < 0) {
            fprintf(stderr, "stat error\n");
            exit(1);
        }

        Node *newNode = createNode(entry->d_name);
        addNode(newNode);
        if ((int)strlen(newNode->fileName) > maxLength)
            maxLength = (int)strlen(newNode->fileName);
    }

    maxLength++;
    closedir(dp);
}

void getTerminalWidth(char *output) {
    int fd;
    pid_t pid;
    char buf[1024];
    int length;

    if ((fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "open error\n");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        execl("/bin/stty", "stty", "size", (char *)0);
        close(fd);

        exit(0);
    }
    else {
        pid = wait(NULL);
    }

    if ((fd = open(output, O_RDONLY)) < 0) {
        fprintf(stderr, "open error\n");
        exit(1);
    }

    read(fd, buf, 1024);
    buf[strlen(buf) - 1] = '\0';
    int i = 0;
    while (buf[i] != ' ') i++;
    while (buf[++i] != '\0') {
        terminalWidth = terminalWidth * 10 + (buf[i] - '0');
    }

    if (remove(output) < 0) {
        fprintf(stderr, "remove error\n");
        exit(1);
    }
    close(fd);
}

void printList(int opt) {
    int wordPerLine = terminalWidth / maxLength;
    if (wordPerLine > 10) wordPerLine = 10;

    int cnt = 0;
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        if (!(opt & OPT_A) && cur->fileName[0] == '.') {
            cur = cur->next;
            continue;
        }
        int tab = maxLength - (int)strlen(cur->fileName);
        printf("%s", cur->fileName);
        for (int i = 0; i < tab; i++) printf(" ");
        cnt++;
        if (cnt % wordPerLine == 0) printf("\n");
    }
}

void ls(int argc, char **argv) {
    int opt = 0b00000;
    int cmd;
    while ((cmd = getopt(argc, argv, "a")) != -1) {
        switch(cmd) {
            case 'a':
                opt |= OPT_A;
                break;
            //
            // case 'l':
            //     opt |= OPT_L;
            //     break;
            //
            // case 'i':
            //     opt |= OPT_I;
            //     break;
            //
            case '?':
                printf("Unknown flag : %c\n", optopt);
                break;
        }
    }
    makeList();
    getTerminalWidth("termWidth.txt");

    printList(opt);

    deleteNode();
    printf("\n\n");
}
