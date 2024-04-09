#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polish_notation.h"
#include "queue.h"
#include "stack.h"
#include "stack_double.h"

#define Operations "+", "-", "/", "(", ")", "*", "sin", "cos", "tan", "ctg", "sqrt", "ln"
#define Operations_count 12

#define HEIGHT 25
#define WIDTH 80

#define EPS 1e-6

void drawGraph(Queue* queue, int len);
void clearGraph(char graph[][WIDTH]);
int isOperation(char* buf);
double getValueBinary(StackDouble* stack, char* operation);
double getValueUnary(StackDouble* stack, char* operation);
double getResult(Queue* queue, double x, int len);
int characterRead(Queue* queue, Stack* stack, int* len);
int characterSort(char ch, char previous_char, Queue* queue, Stack* stack);
char operationExist(char ch);
size_t* lengthOfOperations(char** operations);
char singleCharacterSearch(char search_ch, char** operations, const size_t* array_of_lengths);
char doubleCharacterSearch(char search_ch, char search_ch_2, char** operations,
                           const size_t* array_of_lengths);
char tripleCharacterSearch(char search_ch, char search_ch_2, char search_ch_3, char** operations,
                           const size_t* array_of_lengths);
char quadrupleCharacterSearch(char search_ch, char search_ch_2, char search_ch_3, char search_ch_4,
                              char** operations, const size_t* array_of_lengths);
char* charToString(char ch);
void makeString(Queue* queue, Stack* stack, char ch);

int main() {
    Stack* stack;
    Queue* queue;
    stack = malloc(sizeof(Stack));
    queue = malloc(sizeof(Queue));
    initStack(stack);
    initQueue(queue);
    int len = 0;

    if (characterRead(queue, stack, &len)) {
        printQueue(queue);
        printf("\n");
        drawGraph(queue, len);
    } else {
        printf("ERROR");
    }

    free(stack);
    free(queue);
}

int characterRead(Queue* queue, Stack* stack, int* len) {
    int error = 0;
    char ch = getchar();
    char previous_char = ' ';
    while ((ch != '\n') && (error == 0)) {
        error = (characterSort(ch, previous_char, queue, stack));
        if (ch != '(' && ch != ')') {
            (*len)++;
        }
        previous_char = ch;
        ch = getchar();
    }
    addOperation(stack, queue, " ");
    return (1 - error);
}

int characterSort(char ch, char previous_char, Queue* queue, Stack* stack) {
    int exist = 1;
    if (ch == 'x') {
        addOperand(queue, "x");
    } else if (ch >= '0' && ch <= '9') {
        makeString(queue, stack, ch);
    } else {
        char test = operationExist(ch);
        if ((test == '-') && ((previous_char == ' ') || (previous_char == '('))) {
            addOperation(stack, queue, "~");
        } else if (test != 'w') {
            makeString(queue, stack, test);
        } else {
            exist = 0;
        }
    }
    return (1 - exist);
}

char operationExist(char ch) {
    char answer;
    char* array_of_operations[] = {Operations};
    char second_ch, third_ch;
    size_t* array_of_lengths = lengthOfOperations(array_of_operations);
    answer = singleCharacterSearch(ch, array_of_operations, array_of_lengths);
    if (answer == 'n') {
        second_ch = getchar();
        answer = doubleCharacterSearch(ch, second_ch, array_of_operations, array_of_lengths);
    }
    if (answer == 'n') {
        third_ch = getchar();
        answer = tripleCharacterSearch(ch, second_ch, third_ch, array_of_operations, array_of_lengths);
    }
    if (answer == 'n') {
        char fourth_ch = getchar();
        answer = quadrupleCharacterSearch(ch, second_ch, third_ch, fourth_ch, array_of_operations,
                                          array_of_lengths);
    }
    free(array_of_lengths);
    return answer;
}

size_t* lengthOfOperations(char** operations) {
    size_t* array_of_lengths = malloc(Operations_count * sizeof(size_t));
    for (int i = 0; i < Operations_count; i++) {
        size_t len = strlen(operations[i]);
        array_of_lengths[i] = len;
    }
    return array_of_lengths;
}

char singleCharacterSearch(char search_ch, char** operations, const size_t* array_of_lengths) {
    int i = 0;
    char found_ch = 'w';
    while ((found_ch == 'w') && (i < Operations_count)) {
        if ((array_of_lengths[i] == 1) && (operations[i][0] == search_ch))
            found_ch = search_ch;
        else if ((array_of_lengths[i] > 1) && (operations[i][0] == search_ch))
            found_ch = 'n';
        i++;
    }
    return found_ch;
}

char doubleCharacterSearch(char search_ch, char search_ch_2, char** operations,
                           const size_t* array_of_lengths) {
    int i = 0;
    char found_ch = 'w';
    while ((found_ch == 'w') && (i < Operations_count)) {
        if ((array_of_lengths[i] == 2) && (operations[i][0] == search_ch) &&
            (operations[i][1] == search_ch_2))
            found_ch = search_ch;
        else if ((array_of_lengths[i] > 2) && (operations[i][0] == search_ch) &&
                 (operations[i][1] == search_ch_2))
            found_ch = 'n';
        i++;
    }
    return found_ch;
}

char tripleCharacterSearch(char search_ch, char search_ch_2, char search_ch_3, char** operations,
                           const size_t* array_of_lengths) {
    int i = 0;
    char found_ch = 'w';
    while ((found_ch == 'w') && (i < Operations_count)) {
        if ((array_of_lengths[i] == 3) && (operations[i][0] == search_ch) &&
            (operations[i][1] == search_ch_2) && (operations[i][2] == search_ch_3))
            found_ch = search_ch_2;
        else if ((array_of_lengths[i] > 3) && (operations[i][0] == search_ch) &&
                 (operations[i][1] == search_ch_2) && (operations[i][2] == search_ch_3))
            found_ch = 'n';
        i++;
    }
    return found_ch;
}

char quadrupleCharacterSearch(char search_ch, char search_ch_2, char search_ch_3, char search_ch_4,
                              char** operations, const size_t* array_of_lengths) {
    int i = 0;
    char found_ch = 'w';
    while ((found_ch == 'w') && (i < Operations_count)) {
        if ((array_of_lengths[i] == 4) && (operations[i][0] == search_ch) &&
            (operations[i][1] == search_ch_2) && (operations[i][2] == search_ch_3) &&
            (operations[i][3] == search_ch_4))
            found_ch = search_ch_2;
        i++;
    }
    return found_ch;
}

void makeString(Queue* queue, Stack* stack, char ch) {
    ch == '0'   ? addOperand(queue, "0")
    : ch == '1' ? addOperand(queue, "1")
    : ch == '2' ? addOperand(queue, "2")
    : ch == '3' ? addOperand(queue, "3")
    : ch == '4' ? addOperand(queue, "4")
    : ch == '5' ? addOperand(queue, "5")
    : ch == '6' ? addOperand(queue, "6")
    : ch == '7' ? addOperand(queue, "7")
    : ch == '8' ? addOperand(queue, "8")
    : ch == '9' ? addOperand(queue, "9")
    : ch == '+' ? addOperation(stack, queue, "+")
    : ch == '-' ? addOperation(stack, queue, "-")
    : ch == '*' ? addOperation(stack, queue, "*")
    : ch == '/' ? addOperation(stack, queue, "/")
    : ch == '(' ? addOperation(stack, queue, "(")
    : ch == ')' ? addOperation(stack, queue, ")")
    : ch == 'i' ? addOperation(stack, queue, "i")
    : ch == 'o' ? addOperation(stack, queue, "o")
    : ch == 'a' ? addOperation(stack, queue, "a")
    : ch == 't' ? addOperation(stack, queue, "t")
    : ch == 'q' ? addOperation(stack, queue, "q")
                : addOperation(stack, queue, "l");
}

void drawGraph(Queue* queue, int len) {
    double xmin = 0.0;
    double xmax = 4 * M_PI;
    double ymin = -1.0;
    double ymax = 1.0;

    double x_range = xmax - xmin;
    double y_range = ymax - ymin;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real_x = xmin + (x_range * x / (WIDTH - 1));
            double real_y = ymin + (y_range * y / (HEIGHT - 1));

            double value = getResult(queue, real_x, len);

            if (fabs(value - real_y) < y_range / HEIGHT) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

double getResult(Queue* queue, double x, int len) {
    StackDouble* stack;
    stack = malloc(sizeof(StackDouble));
    initStackDouble(stack);
    int i = 1;
    int flag = 0;
    double res;

    while (i <= len) {
        char* buf = queue->elem[i];

        if (strcmp(buf, "x") == 0 && i == len && i == 1) {
            res = x;
            flag = 1;
        } else if ((*buf >= '0' || *buf <= '9') && i == len && i == 1) {
            res = atof(buf);
            flag = 1;
        }
        i++;
        while (!isOperation(buf) && flag == 0) {
            if (strcmp(buf, "x") == 0) {
                pushStackDouble(stack, x);
            } else {
                pushStackDouble(stack, atof(buf));
            }
            buf = queue->elem[i];
            i++;
        }
        if (!flag) {
            if (strcmp(buf, "~") == 0 || strcmp(buf, "i") == 0 || strcmp(buf, "o") == 0 ||
                strcmp(buf, "a") == 0 || strcmp(buf, "t") == 0 || strcmp(buf, "l") == 0 ||
                strcmp(buf, "q") == 0) {
                pushStackDouble(stack, getValueUnary(stack, buf));
            } else {
                pushStackDouble(stack, getValueBinary(stack, buf));
            }
        }
    }
    free(stack);
    if (!flag) {
        res = popStackDouble(stack);
    }
    return res;
}

double getValueBinary(StackDouble* stack, char* operation) {
    double a = popStackDouble(stack);
    double b = popStackDouble(stack);

    double res = 0;
    if (strcmp(operation, "+") == 0) {
        res = a + b;
    } else if (strcmp(operation, "-") == 0) {
        res = b - a;
    } else if (strcmp(operation, "*") == 0) {
        res = a * b;
    } else if (strcmp(operation, "/") == 0) {
        if (a < EPS) {
            res = 0.000000001;
        } else {
            res = b / a;
        }
    }
    return res;
}

double getValueUnary(StackDouble* stack, char* operation) {
    double a = popStackDouble(stack);
    double res;
    if (strcmp(operation, "i") == 0) {
        res = sin(a);
    } else if (strcmp(operation, "o") == 0) {
        res = cos(a);
    } else if (strcmp(operation, "a") == 0) {
        res = tan(a);
    } else if (strcmp(operation, "t") == 0) {
        res = 1 / tan(a);
    } else if (strcmp(operation, "q") == 0) {
        res = sqrt(a);
    } else if (strcmp(operation, "l") == 0) {
        res = log(a);
    } else {
        res = -a;
    }
    return res;
}

int isOperation(char* buf) {
    int res = 0;
    if (strcmp(buf, "+") == 0 || strcmp(buf, "-") == 0 || strcmp(buf, "*") == 0 || strcmp(buf, "/") == 0 ||
        strcmp(buf, "~") == 0 || strcmp(buf, "i") == 0 || strcmp(buf, "o") == 0 || strcmp(buf, "a") == 0 ||
        strcmp(buf, "t") == 0 || strcmp(buf, "q") == 0 || strcmp(buf, "l") == 0) {
        res++;
    }
    return res;
}
