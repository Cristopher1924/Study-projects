#ifndef STACK_H
#define STACK_H

#define NMAX 1000

typedef struct Stack {
    char *elem[NMAX];
    int top;
} Stack;

void initStack(Stack *stack);
void pushStack(Stack *stack, char *operator);
char *popStack(Stack *stack);
char *getTopStack(Stack *stack);
int isEmptyStack(Stack *stack);

#endif
