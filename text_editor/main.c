#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#define MAX_FILE_LEN 500

void sig_winch(int signo) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}



int file_open(WINDOW *wnd) {
    char filename[10];
    char filetext[MAX_FILE_LEN];
    wprintw(wnd, "Input file name\n");
    wgetnstr(wnd, filename, 10);
    filename[10] = 0;
    FILE *fl = fopen(filename, "r");
    fread(filetext, sizeof(char), MAX_FILE_LEN, fl);

    printw("%s", filetext);
    refresh();

    fclose(fl);
    return 0;
}



int file_save(WINDOW *wnd, char *filename){
    wprintw(wnd, "Input file name\n");
    wgetnstr(wnd, filename, 10);
    filename[10] = 0;
    FILE *fw = fopen(filename, "w");
    char str[MAX_FILE_LEN];

    wgetstr(wnd, str);
    fwrite(str, sizeof(char), MAX_FILE_LEN, fw);

    fclose(fw);
    return 0;
}



int main(int argc, char ** argv)
{
    WINDOW * wnd;
    char filename[11];
    initscr();
    signal(SIGWINCH, sig_winch);
    curs_set(TRUE);
    start_color();
    refresh();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);


    wnd = newwin(5, 23, 2, 2);
    keypad(wnd, 1);
    refresh();


    int x = 0, y = 0;
    char ch;
    int ch1;
    move(y, x);
    refresh();

/* editing */
    for(;;) {
        ch1 = getch();
        if (ch == 70) file_open(wnd);
        if (ch == 71) file_save(wnd, filename);
        if (ch == 72) {
            endwin();
            exit(EXIT_SUCCESS);
        }
        if (ch == '\n') {
            move(0, y++);
        } else {
            mvwaddch(wnd, y, x, ch);
            move(y, x++);
        }
    }

}