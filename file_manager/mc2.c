#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <dirent.h>

#define WINDOW_WIDTH 50
#define WINDOW_HEIGHT 25
#define MAX_STR_LENGTH 20

int open_dir(char *dir_name){
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(1);
    };

    while ( (entry = readdir(dir)) != NULL) {
        printw("%s \n", entry->d_name);
    };
}

int main(int argc, char ** argv)
{
    WINDOW * wnd_left;
    WINDOW * subwnd;
    initscr();

    curs_set(TRUE);
    start_color();
    refresh();
    init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);

    wnd = newwin(5, 18, 2, 4);
    wattron(wnd, COLOR_PAIR(1));
    box(wnd, '|', '-');

    DIR *dir;
    struct dirent *entry;
    keypad(wnd, TRUE);
    char str[MAX_STR_LENGTH];
    int ch;

    open_dir(".");
    ch = getch();
    switch(ch){
        case KEY_ENTER:
            winstr(wnd_left, str);
            open_dir(str);
            break;
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        default:
            break;
    }

/*
    dir = opendir(".");
    if (!dir) {
        perror("diropen");
        exit(1);
    };

    while ( (entry = readdir(dir)) != NULL) {
        printw("%s \n", entry->d_name);
    };

    closedir(dir);


    subwnd = derwin(wnd, 3, 16, 1, 1);
    wbkgd(subwnd, COLOR_PAIR(2));
    wattron(subwnd, A_BOLD);
    wprintw(subwnd, "Hello, brave new curses world!\n");
    wrefresh(subwnd);
    wrefresh(wnd);
    delwin(subwnd);
    delwin(wnd);
    wmove(stdscr, 8, 1);
    */
    printw("Press any key to continue...");
    refresh();
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}