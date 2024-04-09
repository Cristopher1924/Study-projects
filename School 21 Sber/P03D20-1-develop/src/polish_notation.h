#include "queue.h"
#include "stack.h"

void addOperand(Queue *queue, char *operand);
void addOperation(Stack *stack, Queue *queue, char *operation);
int getPriority(char *operation);
void printStatus(Queue *queue, Stack *stack);
