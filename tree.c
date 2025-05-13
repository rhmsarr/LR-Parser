#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_TREE_LENGTH 100

static Node* tree[MAX_TREE_LENGTH];
static int top = -1;

Node* newNode(const char* content, int childNumber) {
    Node* node = (Node*) malloc(sizeof(Node));
    
    strncpy(node->content, content, sizeof(node->content) - 1);
    node->content[sizeof(node->content) - 1] = '\0';
    node->childNumber = childNumber;
    node->children = (Node**) malloc(sizeof(Node*) * childNumber);
    return node;
}

void pushT(Node* node) {
    if (top >= MAX_TREE_LENGTH - 1) {
        printf("The tree is full\n");
    }
    tree[++top] = node;
}

Node* popT() {
    if (top < 0) {
        printf("The tree is empty.\n");
    }
    return tree[top--];
}

Node* topT() {
    if (top < 0) return NULL;
    return tree[top];
}

static void printTreeRecursive(Node* node, char* currentPath) {
    char newPath[1000];
    snprintf(newPath, sizeof(newPath), "%s/%s", currentPath, node->content);

  
    printf("%s\n", newPath);

    for (int i = 0; i < node->childNumber; ++i) {
        printTreeRecursive(node->children[i], newPath);
    }

}

void printTree(Node* root) {
    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    printTreeRecursive(root, "");
}
