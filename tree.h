#ifndef TREE_H
#define TREE_H

typedef struct Node {
    char content[10];            
    struct Node** children; 
    int childNumber;
} Node;

Node* newNode(const char* content, int childNumber);

void pushT(Node* node);
Node* popT();
Node* topT();

void printTree(Node* root);

#endif
