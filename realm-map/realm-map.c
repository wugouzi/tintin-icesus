#include "ncurses.h"
#include "stdlib.h"
#include <stdio.h>
#include "string.h"
#include "unistd.h"


#define COLOR_LG 11
#define COLOR_DG 12
#define COLOR_YE 13
#define COLOR_GR 14
#define COLOR_MA 15
#define COLOR_DB 16
#define COLOR_LB 17
#define COLOR_BR 18
#define COLOR_RE 19
#define COLOR_WH 20
#define COLOR_TZ 21

#define P_COLOR_LG 1
#define P_COLOR_DG 2
#define P_COLOR_YE 3
#define P_COLOR_GR 4
#define P_COLOR_MA 5
#define P_COLOR_DB 6
#define P_COLOR_LB 7
#define P_COLOR_BR 8
#define P_COLOR_RE 9
#define P_COLOR_WH 10
#define P_COLOR_TZ 11

char buf[1000][1000];
int maph, mapw;
int WIN_H = 20, WIN_W = 30;

void printing()
{
    addstr("This was printed using addstr\n\n");
    refresh();

    addstr("The following letter was printed using addch:- ");
    addch('a');
    refresh();

    printw("\n\nThese numbers were printed using printw\n%d\n%f\n", 123, 456.789);
    refresh();
}

void moving_and_sleeping()
{
    int row = 5;
    int col = 0;

    curs_set(0);

    for(char c = 65; c <= 90; c++)
    {
        move(row++, col++);
        addch(c);
        refresh();
        napms(100);
    }

    row = 5;
    col = 3;

    for(char c = 97; c <= 122; c++)
    {
        mvaddch(row++, col++, c);
        refresh();
        napms(100);
    }

    curs_set(1);

    addch('\n');
}

void colouring()
{
    if(has_colors())
    {
        if(start_color() == OK)
        {
            init_pair(1, COLOR_YELLOW, COLOR_RED);
            init_pair(2, COLOR_GREEN, COLOR_GREEN);
            init_pair(3, COLOR_MAGENTA, COLOR_CYAN);

            attrset(COLOR_PAIR(1));
            addstr("Yellow and red\n\n");
            refresh();
            attroff(COLOR_PAIR(1));

            attrset(COLOR_PAIR(2) | A_BOLD);
            addstr("Green and green A_BOLD\n\n");
            refresh();
            attroff(COLOR_PAIR(2));
            attroff(A_BOLD);

            attrset(COLOR_PAIR(3));
            addstr("Magenta and cyan\n");
            refresh();
            attroff(COLOR_PAIR(3));
        }
        else
        {
            addstr("Cannot start colours\n");
            refresh();
        }
    }
    else
    {
        addstr("Not colour capable\n");
        refresh();
    }
}

int color_init(void) {
    if (!has_colors()) {
        addstr("\nNo colour available\n");
        refresh();
        return -1;
    }
    if (start_color() != OK) {
        addstr("\nCannot start colours\n");
        refresh();
        return -1;
    }
    init_color(COLOR_LG, 90, 247, 142);
    init_color(COLOR_DG, 80, 250, 123);
    init_color(COLOR_YE, 255, 255, 128);
    init_color(COLOR_GR, 241, 250, 140);
    init_color(COLOR_MA, 255, 121, 198);
    init_color(COLOR_DB, 189, 147, 249);
    init_color(COLOR_LB, 202, 169, 250);
    init_color(COLOR_BR, 255, 255, 255);
    init_color(COLOR_RE, 255, 0, 0);
    init_color(COLOR_WH, 255, 255, 255);
    init_color(COLOR_TZ, 97, 195, 162);
    init_pair(P_COLOR_LG, COLOR_GREEN, COLOR_BLACK);
    init_pair(P_COLOR_DG, COLOR_GREEN, COLOR_BLACK);
    init_pair(P_COLOR_YE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(P_COLOR_GR, COLOR_WHITE, COLOR_BLACK);
    init_pair(P_COLOR_MA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(P_COLOR_DB, COLOR_BLUE, COLOR_BLACK);
    init_pair(P_COLOR_LB, COLOR_BLUE, COLOR_BLACK);
    init_pair(P_COLOR_BR, COLOR_CYAN, COLOR_BLACK);
    init_pair(P_COLOR_RE, COLOR_RED, COLOR_BLACK);
    init_pair(P_COLOR_WH, COLOR_WHITE, COLOR_BLACK);
    init_pair(P_COLOR_TZ, COLOR_GREEN, COLOR_BLACK);
    return 0;
}

void putcch(char ch) {
    switch (ch) {
        case '^':
            attrset(COLOR_PAIR(P_COLOR_GR));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_GR));
            break;
        case 'g':
            attrset(COLOR_PAIR(P_COLOR_WH));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_WH));
            break;
        case 'e':
            attrset(COLOR_PAIR(P_COLOR_LG));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_LG));
            break;
        case 'E':
            attrset(COLOR_PAIR(P_COLOR_DG));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_DG));
            break;
        case 'p':
            attrset(COLOR_PAIR(P_COLOR_YE));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_YE));
            break;
        case '?':
            attrset(COLOR_PAIR(P_COLOR_MA));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_MA));
            break;
        case 'r':
            attrset(COLOR_PAIR(P_COLOR_DB));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_DB));
            break;
        case 'i':
            attrset(COLOR_PAIR(P_COLOR_LB));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_LB));
            break;
        case 'h':
            attrset(COLOR_PAIR(P_COLOR_BR));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_BR));
            break;
        case 's':
            attrset(COLOR_PAIR(P_COLOR_RE));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_RE));
            break;
        case 't':
            attrset(COLOR_PAIR(P_COLOR_TZ));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_TZ));
            break;
        case '$':
            attrset(COLOR_PAIR(P_COLOR_RE));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_RE));
            break;
        default:
            attrset(COLOR_PAIR(P_COLOR_WH));
            addch(ch);
            attroff(COLOR_PAIR(P_COLOR_WH));
    }

}

void read_map(FILE* map) {
    int i = 0;
    char c;
    while (fgets(buf[i], sizeof buf[i], map)) {
        buf[i][strcspn(buf[i], "\n")] = '\0';
        i++;
    }
    maph = i;
    mapw = strlen(buf[0]);
}

void draw(int x, int y) {
    int x0, y0, x1, y1;
    if (x < WIN_H/2) {
        x0 = 0;
        x1 = WIN_H;
    } else if (x > maph-WIN_H/2) {
        x1 = maph;
        x0 = maph-WIN_H;
    } else {
        x0 = x-WIN_H/2;
        x1 = x0+WIN_H;
    }
    if (y < WIN_W/2) {
        y0 = 0;
        y1 = WIN_W;
    } else if (y > maph-WIN_W/2) {
        y1 = mapw;
        y0 = mapw-WIN_W;
    } else {
        y0 = y-WIN_W/2;
        y1 = y0+WIN_W;
    }
    for (int i = x0; i < x1; i++) {
        for (int j = y0; j < y1; j++)
            if (i == x && j == y)
                putcch('$');
            else
                putcch(buf[i][j]);
        addch('\n');
    }
}

void update(char* coord_name) {
    int x, y;
    int i=0;
    while (1) {
        FILE* fp = fopen(coord_name, "r");
        fscanf(fp, "%d %d", &x, &y);
        //printw("%d %d %d\n", i++, x, y);
        //refresh();
        draw(x, y);
        refresh();
        clear();
        sleep(1);
    }
}

int main(void)
{
    initscr();

    if(color_init()<0) {
        return EXIT_FAILURE;
    }

    refresh();


    char* map_name = "map";
    char* coord_name = "coord";

    FILE* map_file = fopen(map_name, "r");

    read_map(map_file);
    update(coord_name);

    endwin();

    return EXIT_SUCCESS;
}
