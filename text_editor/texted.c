#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#define MAX_FILE_LEN 500

int init_win(){
    move(0, 0);
    box(stdscr, '|', '-');
    printw("| F1 - open | F2 - save | F3 - exit |");
    move(1, 1);
}

int init_subwin(char *filename){
    WINDOW *subw = newwin(5, 20, 10, 2);
    box(subw, '|', '-');
    wprintw(subw, "Input file name\n");
    wmove(subw, 1, 1);
    wgetstr(subw, filename);
    delwin(subw);
    return 0;
}

int file_open() {
    char filename[11];
    char filetext[MAX_FILE_LEN];

    init_subwin(filename);
    init_win();

    FILE *fl = fopen(filename, "r");
    fscanf(fl, "%s", filetext);

    printw("%s", filetext);
    refresh();

    fclose(fl);
    return 0;
}


int file_save(){
    char filename[11];
    char str[MAX_FILE_LEN];

    init_subwin(filename);
    init_win();

    FILE *fw = fopen(filename, "w");
    move(1, 1);
    instr(str);

    printw("%s", str);
    fprintf(fw ,"%s", str);

    fclose(fw);
    return 0;
}
