#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "string_stack.h"

#define MAX_SIZE 100



void initializeStack(Stack *s){
    s->top = -1;
}

bool stackIsEmpty(Stack *s){
    return s->top == -1;
}

bool stackIsFull(Stack *s){
    return s->top == MAX_SIZE -1;
}
void push(Stack *s, const char* item){
    if(!stackIsFull(s)){
        s->top++;
        s->items[s->top] = (char*)malloc(MAX_SIZE);
        strncpy(s->items[s->top], item, MAX_SIZE-1);
        s->items[s->top][MAX_SIZE - 1] = '\0';
    }
}

char* pop(Stack* s) {
    if (!stackIsEmpty(s)) {
        char* item = s->items[s->top];
        s->top--;
        return item;
    }
    printf("Stack is empty\n");
    return NULL;
}

char* peekS(Stack* s) {
    if (!stackIsEmpty(s)) {
        char* item = s->items[s->top];
        return item;
    }
    printf("Stack is empty\n");
    return NULL;
}

void printStack(Stack* s){
    int length = 0;
    for(int i = 0; i<= s->top; i++){
        printf("%-1s", s->items[i]);
        length+= strlen(s->items[i]);
    }

    for(int i = length; i<50; i++){
        printf(" ");
    }
}

