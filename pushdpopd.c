//Implement pushd and popd Linux commands in C programming.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

// Node structure for stack
typedef struct Node {
    char dir[PATH_MAX];
    struct Node* next;
} Node;

Node* top = NULL;

// Function to push directory onto stack
void pushd(const char* dir) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (getcwd(newNode->dir, sizeof(newNode->dir)) == NULL) {
        perror("getcwd");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    newNode->next = top;
    top = newNode;

    if (chdir(dir) != 0) {
        perror("chdir");
    exit(EXIT_FAILURE);
    }
}

// Function to pop directory from stack
void popd() {
    if (top == NULL) {
        fprintf(stderr, "popd: directory stack empty\n");
        return;
    }
    Node* temp = top;
    top = top->next;

    if (chdir(temp->dir) != 0) {
        perror("chdir");
        free(temp);
        exit(EXIT_FAILURE);
    }
    free(temp);
}

// Function to print the current directory
void print_current_directory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current directory: %s\n", cwd);
    } else {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid Number of arguments list\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "pushd") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Invalid Number of arguments list for pushd \n", argv[0]);
            exit(EXIT_FAILURE);
        }
        pushd(argv[2]);
        print_current_directory();
    } else if (strcmp(argv[1], "popd") == 0) {
        popd();
        print_current_directory();
    } else {
        fprintf(stderr, "Invalid command. Use pushd or popd.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
