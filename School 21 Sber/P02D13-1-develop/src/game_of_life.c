#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80
#define STEP 100000
#define DEAD ' '
#define ALIVE '0'

void clearingTheTable(char table[][WIDTH]);
int checkNeighbors(int i, int j, char copy_table[][WIDTH]);
int startPosition(char table[][WIDTH]);
void printTable(char table[][WIDTH], int speed);
int matrixChecker(char table[][WIDTH]);
void copyTable(char table[][WIDTH], char copy_table[][WIDTH]);
int matrixEquaity(char table[][WIDTH], char copy_table[][WIDTH]);
int pops(char table[][WIDTH]);

int main() {
    char table[HEIGHT][WIDTH];
    char button;
    int speed = 1000000;
    int res = 0;
    clearingTheTable(table);
    if (startPosition(table) != 0) {
        res = 1;
    }
    if (freopen("/dev/tty", "r", stdin) ==
        NULL) {  // reseting input back to stdin so ncurses getch() starts working
        res = 1;
    }
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    refresh();
    while (res == 0) {
        printTable(table, speed);
        res = matrixChecker(table);
        for (int i = 0; i < 5; i++) {
            button = getch();
            switch (button) {
                case '+':
                case '=':
                    if (speed - STEP > 0) {
                        speed -= STEP;
                    } else if (speed - (STEP / 10) > 0) {  // making game fasten slower on high speed
                        speed -= (STEP / 10);
                    }

                    break;
                case '-':
                    if (speed - STEP < 0) {
                        speed += STEP / 10;  // making game slow slower oh high speed to make delay change
                                             // static on high speed
                    }
                    if (speed < STEP * 100) {
                        speed += STEP;
                    }
                    break;
                case 'q':
                    res = 1;
                default:
                    break;
            }
        }
        flushinp();
        usleep(speed);
    }
    echo();
    endwin();
    return 0;
}

int startPosition(char table[][WIDTH]) {
    double n_d;
    int flag = 0;
    if (scanf("%lf", &n_d) != 1 || (int)n_d != n_d) {
        flag = 1;
    }
    if (!flag) {
        double x_d, y_d;
        for (int i = 0; i < (int)n_d; ++i) {
            if (scanf("%lf %lf", &x_d, &y_d) != 2 || (int)x_d != x_d || (int)y_d != y_d) {
                flag = 1;
            } else {
                table[(int)x_d][(int)y_d] = ALIVE;
            }
        }
    }
    return flag;
}

void printTable(char table[][WIDTH], int speed) {
    double tps = 1000000.0 / speed;
    clear();
    printw("press q to exit     current population = %d         %.1lf TPS      +/- to control speed\n",
           pops(table), tps);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printw("%c", table[i][j]);
        }
        printw("\n");
    }
}

void clearingTheTable(char table[][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            table[i][j] = DEAD;
        }
    }
}

int matrixChecker(char table[][WIDTH]) {
    char copy_table[HEIGHT][WIDTH];
    copyTable(table, copy_table);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (table[i][j] == DEAD) {
                if (checkNeighbors(i, j, copy_table) == 3) {
                    table[i][j] = ALIVE;
                }
            } else {
                if (checkNeighbors(i, j, copy_table) < 2 || checkNeighbors(i, j, copy_table) > 3) {
                    table[i][j] = DEAD;
                }
            }
        }
    }
    return matrixEquaity(table, copy_table);
}

int checkNeighbors(int i, int j, char copy_table[][WIDTH]) {
    int sum = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (!(x == 0 && y == 0)) {
                int cur_i = (i + x) % HEIGHT;
                int cur_j = (j + y) % WIDTH;
                if (cur_i < 0) {
                    cur_i = HEIGHT + cur_i;
                }
                if (cur_j < 0) {
                    cur_j = WIDTH + cur_j;
                }
                if (copy_table[cur_i][cur_j] == ALIVE) {
                    sum++;
                }
            }
        }
    }
    return sum;
}

void copyTable(char table[][WIDTH], char copy_table[][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            copy_table[i][j] = table[i][j];
        }
    }
}

int matrixEquaity(char table[][WIDTH], char copy_table[][WIDTH]) {  // checks if there are any changes in tick
    int equal = 1;
    for (int i = 0; i < HEIGHT && equal == 1; ++i) {
        for (int j = 0; j < WIDTH && equal == 1; ++j) {
            if (table[i][j] != copy_table[i][j]) {
                equal = 0;
            }
        }
    }
    return equal;
}

int pops(char table[][WIDTH]) {  // amount of living cells
    int res = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (table[i][j] == ALIVE) {
                res++;
            }
        }
    }
    return res;
}