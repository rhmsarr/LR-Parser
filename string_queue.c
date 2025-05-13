#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#include <stdlib.h>

#include "string_queue.h"



#define MAX_SIZE 100



void initializeQueue(Queue* q){
    q->front = -1;
    q->rear = 0;
}
bool isEmpty(Queue* q){
    return (q->front == q->rear -1);
}
bool isFull(Queue* q){
    return (MAX_SIZE == q->rear);
}

void enqueue(Queue* q, const char* item){
    if(!isFull(q)){
        q->items[q->rear] = (char*)malloc(MAX_SIZE);
        strncpy(q->items[q->rear], item, MAX_SIZE - 1);
        q->items[q->rear][MAX_SIZE - 1] = '\0';
        q->rear++;
    }
    else{
        printf("The queue is full. Cannot add any items.\n");
    }
}

void dequeue(Queue* q){
    if(!isEmpty(q)){
        q->front++;
        return;
    }
    printf("The queue is empty. Cannot remove any items.\n");
}

char* peekQ(Queue* q){
    if(!isEmpty(q)){
        return q->items[q->front+1];
    }
    printf("The queue is empty. Cannot peek at any items.\n");
    
}
void printQueue(Queue* q)
{
    if (!isEmpty(q)) {
        int length = 0;
        for (int i = q->front + 1; i < q->rear; i++) {
            printf("%s ", q->items[i]);
            length+= strlen(q->items[i]) + 1;
        }
        for(int i = length; i<=50; i++){
            printf(" ");
        }
        return;
    }
    printf("The queue is empty. Cannot print any items.\n");

   
}

