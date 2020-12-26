#ifndef JAYMATRIX_MAIN_H
#define JAYMATRIX_MAIN_H
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#include "default.h"
#include "coordinates.h"

//#define JMTRX_DEBUG_ARGS
//#define JMTRX_DEBUG_INIT

#ifdef JMTRX_DEBUG_ARGS
#include <stdio.h>
#endif

#define RNG_COLOR(max) (attron(COLOR_PAIR(rand() % max + 1)))
#define IS_PREFIX(pre, str) (!strncmp(pre, str, strlen(pre)))
#define STR_EQ(x1, x2) (!strcmp(x1, x2))
int main(int, char **);

#endif
