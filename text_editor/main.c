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
    printw("Input file name\n");
    getstr(filename);
    filename[10] = 0;
    FILE *fl = fopen(filename, "r");
    //fread(filetext, sizeof(char), MAX_FILE_LEN, fl);
    fscanf(fl, "%s", filetext);
    printw("%s", filetext);
    refresh();

    fclose(fl);
    return 0;
}



int file_save(WINDOW *wnd){
    char filename[11];
    wprintw(wnd, "Input file name\n");
    getstr(filename);
    filename[10] = 0;
    FILE *fw = fopen(filename, "w");
    char str[MAX_FILE_LEN];

    getstr(str);
    fprintf(fw ,"%s", str);

    fclose(fw);
    return 0;
}



int main(int argc, char ** argv)
{
    WINDOW * wnd;
    char filename[11];
    initscr();
    keypad(stdscr, true);
    signal(SIGWINCH, sig_winch);
    curs_set(TRUE);
    wnd = newwin(15, 23, 2, 2);
    noecho();
    refresh();

    int x = 0, y = 0;
    char ch;
    int ch1;
    move(y, x);
    refresh();

    while(ch1 != KEY_F(3))
    {
        ch1 = getch();

        switch (ch1) {
            case KEY_F(1):

                echo();
                file_open(wnd);
                break;
            case KEY_F(2):

                file_save(wnd);
                break;

            case KEY_F(3):
                endwin();
                exit(EXIT_SUCCESS);
                break;

            default:
                break;
        }
    }

/* editing
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
    */
}