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

void ls() {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int maxLength = -1;

    if ((dp = opendir(".")) == NULL) {
        fprintf(stderr, "opendir error\n");
        exit(1);
    }

    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &statbuf) < 0) {
            fprintf(stderr, "stat error\n");
            exit(1);
        }

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->fileName = entry->d_name;
        newNode->next = NULL;
        addNode(newNode);
        
        if ((int)strlen(newNode->fileName) > maxLength)
            maxLength = (int)strlen(newNode->fileName);
    }

    Node *cur = head;
    maxLength++;
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

    closedir(dp);
}
