#ifndef STRING_QUEUE_H

#include <stdio.h>
#include <stdbool.h>


#define MAX_SIZE 100

typedef struct{
    char* items[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* q);
int QueueIsEmpty(Queue* q);
int QueueIsFull(Queue* q);
void enqueue(Queue* q, const char* item);
void dequeue(Queue* q);
char* peekQ(Queue* q);
void printQueue(Queue* q);

#endif