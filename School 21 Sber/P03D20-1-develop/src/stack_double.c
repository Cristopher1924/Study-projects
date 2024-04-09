#include "stack_double.h"

#include <stdio.h>

void initStackDouble(StackDouble *stack) { stack->top = 0; }

void pushStackDouble(StackDouble *stack, double operator) {
    stack->elem[stack->top] = operator;
    stack->top++;
}

double popStackDouble(StackDouble *stack) {
    double elem;
    stack->top--;
    elem = stack->elem[stack->top];
    return elem;
}
