#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initQueue(Queue *queue) {
    queue->front = 1;
    queue->rear = 0;
}

void pushQueue(Queue *queue, char *str) {
    queue->rear++;
    queue->elem[queue->rear] = str;
}

void printQueue(Queue *queue) {
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%s ", queue->elem[i]);
    }
}
