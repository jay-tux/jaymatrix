#ifndef JAYMATRIX_DEFAULT_H
#define JAYMATRIX_DEFAULT_H

#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <ncurses.h>


typedef enum {
    OFF, SINGLE, RAINBOW
} COL_MODE;

#define OFF_STR "OFF"
#define SINGLE_STR "SINGLE"
#define RAINBOW_STR "RAINBOW"

#define JMTRX_FPS 24
#define JMTRX_COL SINGLE
#define JMTRX_STOP ((int)'q')

#define ASCII_START 21
#define ASCII_END 126

char *colstr(COL_MODE);
int msleep(long);
char rng_char(int);
void setup_color(COL_MODE, int, int *);

#endif
