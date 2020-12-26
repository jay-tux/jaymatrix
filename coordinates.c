#ifndef JAYMATRIX_COORD_C
#define JAYMATRIX_COORD_C

#include "coordinates.h"

void populate(window *win, int rows, int cols)
{
    srand(time(NULL));
    win->heads = malloc(cols * sizeof(int));
    win->tails = malloc(cols * sizeof(int));

    win->rows = rows;
    win->cols = cols;

    for(int i = 0; i < cols; i++)
    {
        if(rand() % 100 < HEAD_PROBABILITY)
        {
            win->heads[i] = rand() % rows;
            if(rand() % 100 < TAIL_PROBABILITY * 100 / HEAD_PROBABILITY)
            {
                int offset = TAIL_AVG_DIST + (rand() % (2 * TAIL_RANGE_SZ)) - TAIL_RANGE_SZ;
                if(offset < 1) offset = 1;
                win->tails[i] = (win->heads[i] > offset) ? (win->heads[i] - offset) : (0);
            }
            else win->tails[i] = -1;
        }
        else
        {
            win->heads[i] = -1;
            win->tails[i] = -1;
        }
    }
}

void winclear(window *win)
{
    free(win->heads);
    free(win->tails);
}

int add_head()
{
    return rand() % 100 < SPAWN_PROBABILITY;
}

int add_tail(int head)
{
    if(head > TAIL_AVG_DIST + 2 * TAIL_RANGE_SZ) { return 1; }
    if(head < TAIL_AVG_DIST - 2 * TAIL_RANGE_SZ) { return 0; }

    int mx = TAIL_AVG_DIST + TAIL_RANGE_SZ;
    return (rand() % 100) < (100 * head / (mx * ABS(head - TAIL_AVG_DIST)));
}

#endif
