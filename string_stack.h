#ifndef STRING_STACK_H
#define STRING_STACK_H
#define MAX_SIZE 100


typedef struct{
    char* items[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack* s);
bool stackIsEmpty(Stack* s);
bool stackIsFull(Stack* s);
void push(Stack* s, const char* item);
char* pop(Stack* s);
char* peekS(Stack* s);
void printStack(Stack* s);

#endif