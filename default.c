#ifndef JAYMATRIX_DEFAULT_C
#define JAYMATRIX_DEFAULT_C
#include "default.h"

char *colstr(COL_MODE mode)
{
    switch(mode)
    {
        case OFF:     return "off";
        case SINGLE:  return "single color";
        case RAINBOW: return "rainbow mode";
    }
}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

char rng_char(int init)
{
    if(init) { srand(time(NULL)); }

    return (rand() % (ASCII_END - ASCII_START)) + ASCII_START;
}

void setup_color(COL_MODE col, int init, int *max_color)
{
    if(init) { srand(time(NULL)); }
    if(col == OFF)
    {
        *max_color = 0;
        return;
    }

    start_color();
    if(col == SINGLE)
    {
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        *max_color = 1;
    }
    else //col == RAINBOW
    {
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
        *max_color = 7;
    }
}
#endif
