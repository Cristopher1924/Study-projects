#ifndef STACKDouble_H
#define STACKDouble_H

#define NMAX 1000

typedef struct StackDouble {
    double elem[NMAX];
    int top;
} StackDouble;

void initStackDouble(StackDouble *stack);
void pushStackDouble(StackDouble *stack, double operator);
double popStackDouble(StackDouble *stack);

#endif
