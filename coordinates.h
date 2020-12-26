#ifndef JAYMATRIX_COORD_H
#define JAYMATRIX_COORD_H
#include <time.h>
#include <stdlib.h>

#define TAIL_AVG_DIST 15
#define TAIL_RANGE_SZ 10
#define TAIL_PROBABILITY 50
#define HEAD_PROBABILITY 80
#define SPAWN_PROBABILITY 66
#define ABS(x) (x > 0 ? x : -x)

typedef struct {
    int x;
    int y;
} coord;

typedef struct {
    int *heads;
    int *tails;
    int rows;
    int cols;
} window;

void populate(window *, int, int);
void winclear(window *);
int add_head();
int add_tail(int);
#endif
