#include "polish_notation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

void addOperand(Queue *queue, char *operand) { pushQueue(queue, operand); }

void addOperation(Stack *stack, Queue *queue, char *operation) {
    if (strcmp(operation, " ") == 0) {
        while (!isEmptyStack(stack)) {
            pushQueue(queue, popStack(stack));
        }

    } else if (strcmp(operation, ")") == 0) {
        char *element = popStack(stack);
        while (strcmp(element, "(")) {
            pushQueue(queue, element);
            element = popStack(stack);
        }
    } else if (isEmptyStack(stack) || strcmp(operation, "(") == 0) {
        pushStack(stack, operation);
    } else if (getPriority(operation) > getPriority(getTopStack(stack))) {
        pushStack(stack, operation);
    } else if (getPriority(operation) == getPriority(getTopStack(stack))) {
        pushQueue(queue, popStack(stack));
        pushStack(stack, operation);
    } else {
        pushQueue(queue, popStack(stack));
        addOperation(stack, queue, operation);
    }
}

int getPriority(char *operation) {
    int priority = 0;
    if (strcmp(operation, "(") == 0) {
        priority = 0;
    } else if (strcmp(operation, "+") == 0 || strcmp(operation, "-") == 0) {
        priority = 1;
    } else if (strcmp(operation, "*") == 0 || strcmp(operation, "/") == 0) {
        priority = 2;
    } else if (strcmp(operation, "~") == 0) {
        priority = 4;
    } else {
        priority = 3;
    }
    return priority;
}

// void printStatus(Queue *queue, Stack *stack) {
//     printQueue(queue);
//     printf("\n");
//     printStack(stack);
//     printf("\n\n");
// }
