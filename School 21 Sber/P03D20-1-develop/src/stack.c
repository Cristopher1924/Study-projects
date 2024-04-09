#include "stack.h"

#include <stdio.h>

void initStack(Stack *stack) { stack->top = 0; }

void pushStack(Stack *stack, char *operator) {
    stack->elem[stack->top] = operator;
    stack->top++;
}

char *popStack(Stack *stack) {
    char *elem;
    stack->top--;
    elem = stack->elem[stack->top];
    return elem;
}

char *getTopStack(Stack *stack) { return stack->elem[stack->top - 1]; }

int isEmptyStack(Stack *stack) { return stack->top ? 0 : 1; }
