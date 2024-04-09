#ifndef QUEUE_H
#define QUEUE_H

#define QMAX 1000

typedef struct Queue {
    char *elem[QMAX];
    int front, rear;
} Queue;

void initQueue(Queue *queue);
void pushQueue(Queue *queue, char *str);
void printQueue(Queue *queue);

#endif
