#include "texted.h"
#define MAX_FILE_LEN 500


int main(int argc, char ** argv)
{
    int ch;

    /*
     * Инициализация окон и интерфейса
     * */

    initscr();
    keypad(stdscr, true);
    curs_set(TRUE);
    refresh();
    init_win();

    /*
     * Реализация клавиш управления
     * */

    while(1)
    {
        ch = getch();
        switch (ch) {
            case KEY_F(1):
                file_open();
                break;
            case KEY_F(2):
                file_save();
                break;
            case KEY_F(3):
                endwin();
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }
}