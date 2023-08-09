// my_ls.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct _node {
    char *fileName;
    struct _node *next;
} Node;

Node *head = NULL;
int maxLength = -1;

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

void ls() {
    makeList();

    Node *cur = head;
    int cnt = 0;
    while (cur != NULL) {
        if (cur->fileName[0] == '.') {
            cur = cur->next;
            continue;
        }
        int tab = maxLength - (int)strlen(cur->fileName);
        printf("%s", cur->fileName);
        for (int i = 0; i < tab; i++) {
            printf(" ");
        }
        cur = cur->next;
        cnt++;
        if (cnt % 8 == 0)
            printf("\n");
    }

    deleteNode();
    printf("\n\n");
}
