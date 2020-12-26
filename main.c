#ifndef JAYMATRIX_MAIN_C
#define JAYMATRIX_MAIN_C
#include "main.h"

int parse_args(int argc, char **argv, int *fps, COL_MODE *colmode, int *stop)
{
#ifdef JMTRX_DEBUG_ARGS
    printf("Parsing CLI arguments...\n");
#endif
    char *curr;
    for(int i = 1; i < argc; i++)
    {
#ifdef JMTRX_DEBUG_ARGS
        printf("Argument #%d: %s.\n", i, argv[i]);
#endif
        if(STR_EQ(argv[i], "--fps") || STR_EQ(argv[i], "-f"))
        {
            if(i < argc - 1)
            {
                i++;
                int parsed = atoi(argv[i]);
                if(parsed <= 0)
                    fprintf(stderr, "Failed to parse fps. Value invalid. Using %s %d.\n", argv[i - 1], *fps);
                else
                    *fps = parsed;
#ifdef JMTRX_DEBUG_ARGS
                printf("FPS set to %d.\n", *fps);
#endif
            }
            else
            {
                fprintf(stderr, "Failed to parse fps. No argument given. Using %s %d.\n", argv[i], *fps);
            }
        }
        else if(STR_EQ(argv[i], "--color") || STR_EQ(argv[i], "-c"))
        {
            if(i < argc - 1)
            {
                i++;
                if(STR_EQ(argv[i], OFF_STR))          *colmode = OFF;
                else if(STR_EQ(argv[i], SINGLE_STR))  *colmode = SINGLE;
                else if(STR_EQ(argv[i], RAINBOW_STR)) *colmode = RAINBOW;
                else fprintf(stderr, "Failed to parse color value. %s is invalid. Using %s %s.\n",
                             argv[i], argv[i - 1], colstr(*colmode));
#ifdef JMTRX_DEBUG_ARGS
                printf("Color set to %s.\n", colstr(*colmode));
#endif
            }
            else
            {
                fprintf(stderr, "Failed to parse color value. No argument given. Using %s %s.\n",
                        argv[i], colstr(*colmode));
            }
        }
        else if(STR_EQ(argv[i], "--exit") || STR_EQ(argv[i], "-e"))
        {
            if(i < argc - 1)
            {
                i++;
                if(strlen(argv[i]) == 1) *stop = (int)*argv[i]; //single char/digit
                else if(STR_EQ("space", argv[i]))  *stop = (int)' ';
                else if(STR_EQ("return", argv[i])) *stop = KEY_ENTER;
                else if(STR_EQ("tab", argv[i]))    *stop = KEY_STAB;
                else if(IS_PREFIX("FKEY", argv[i]))
                {
                    int fkey = atoi(argv[i] + 4);
                    if(fkey > 0 && fkey < 13) *stop = KEY_F(fkey);
                    else fprintf(stderr, "Failed to parse exit key value. %s is invalid.\n");
                }
#ifdef JMTRX_DEBUG_ARGS
                printf("Updated key exit.\n");
#endif
            }
            else
            {
                fprintf(stderr, "Failed to parse exit key value. No argument given.\n");
            }
        }
        else if(STR_EQ(argv[i], "--help") || STR_EQ(argv[i], "-h"))
        {
            //show help
            printf(" +===============+\n");
            printf(" |   JAYMATRIX   |\n");
            printf(" +===============+\n");
            printf("Custom version of the cmatrix program.\n");
            printf("\n");
            printf("Usage:\n");
            printf("------\n");
            printf("-h or --help:\n");
            printf("   Shows this help page.\n");
            printf("-f or --fps:\n");
            printf("   Sets the speed of the animation in fps (default = 24).\n");
            printf("-c or --color:\n");
            printf("   Sets the color mode. There are 3 color modes (case-sensitive!):\n");
            printf("      OFF:     disables colors, renders in current back/fore colors.\n");
            printf("      SINGLE:  uses the typical colors for cmatrix: green on black (default).\n");
            printf("      RAINBOW: uses random colors; a bit like `cmatrix | lolcat`.\n");
            printf("-e or --exit:\n");
            printf("   Sets the exit key (default = q). Is any of the following values:\n");
            printf("      a single character: uses that key as exit code,\n");
            printf("      a single digit: uses the number key as exit code,\n");
            printf("      space, return, tab: uses the specified key, or\n");
            printf("      FKEY<int>: uses F<int> as exit key.\n");
            printf("When invalid arguments are passed, they are ignored.\n");
            printf("Repeated arguments override each other.\n");
            return 1;
        }
        else
        {
            fprintf(stderr, "Argument %s unknown. Use -h (or --help) for help.\n", argv[i]);
        }
    }

#ifdef JMTRX_DEBUG_ARGS
    printf("%d arguments parsed.\n", argc);
#endif
    return 0;
}

void printwin(window *win)
{
#ifdef JMTRX_DEBUG_INIT
    printf("--- Window (%dx%d) ---\n", win->rows, win->cols);
    for(int r = 0; r < win->rows; r++)
    {
        if(win->heads[r] == -1)
        {
            printf("Row %d has no current curtain.\n", r);
        }
        else
        {
            printf("Row %d's curtain's head is at %d, ", r, win->heads[r]);
            if(win->tails[r] == -1)
            {
                printf("no tail yet.\n");
            }
            else
            {
                printf("tail is at %d (length %d).\n", win->tails[r], win->heads[r] - win->tails[r]);
            }
        }
    }
    printf("--- End of Window ---");
#endif
}

void clrscr(int rows, int cols)
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            mvaddch(row, col, ' ');
        }
    }
}

void get_init(window* win, int maxcol)
{
    if(maxcol != 0) { attron(COLOR_PAIR(1)); }
    clrscr(win->rows, win->cols);
    for(int col = 0; col < win->cols; col++)
    {
        if(win->heads[col] != -1)
        {
            for(int row = win->heads[col]; row > win->tails[col]; row--)
            {
                if(maxcol > 1) { RNG_COLOR(maxcol); }
                mvaddch(row, col, rng_char(0));
            }
        }
    }
}

void render(window *win, int maxcol, int init)
{
    if(init)
    {
        get_init(win, maxcol);
        refresh();
        return;
    }

    for(int col = 0; col < win->cols; col++)
    {
        if(win->heads[col] == -1)
        {
            //start new curtain
            if(add_head()) { win->heads[col] = 0; }
        }
        else
        {
            //continue
            win->heads[col]++;
            if(win->heads[col] < win->rows)
            {
                if(maxcol > 0) { RNG_COLOR(maxcol); }
                mvaddch(win->heads[col], col, rng_char(0));
            }

            if(win->tails[col] != -1)
            {
                mvaddch(win->tails[col], col, ' '); //clear after tail

                win->tails[col]++;
                if(win->tails[col] >= win->rows) //tail out of bounds
                {
                    win->heads[col] = -1;
                    win->tails[col] = -1;
                }
            }

            if(win->tails[col] == -1 && add_tail(win->heads[col])) { win->tails[col] = 0; }
        }
    }
    refresh();
}

int main(int argc, char **argv)
{
    int fps = JMTRX_FPS;
    COL_MODE colormode = JMTRX_COL;
    int stop = JMTRX_STOP;
    long delay = 1000/fps;
    if(parse_args(argc, argv, &fps, &colormode, &stop))
    {
        return 0;
    }
#ifdef JMTRX_DEBUG_ARGS
    printf("Delay: %ld ms.\n", delay);
    return 0;
#endif

    setlocale(LC_ALL, "");
    initscr(); cbreak(); noecho();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    window main;
    populate(&main, rows, cols);
    int colcnt;
    setup_color(colormode, 0, &colcnt);
    nodelay(stdscr, 1);
    curs_set(0);
    render(&main, colcnt, 1);

#ifndef JMTRX_DEBUG_INIT
    int key;
    while(1)
    {
        key = getch();
        if(key != ERR && key == stop) break;
        render(&main, colcnt, 0);
        msleep(delay);
    }
#endif
    endwin();
    printwin(&main);
    winclear(&main);
}

#endif
