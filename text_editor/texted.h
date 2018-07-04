#ifndef __TEXTED_H__
#define __TEXTED_H__


#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>



/*
 * Функция, создающая интерфейса главного окна
 * */

int init_win();

/*
 * Функция, создающая интерфейс подокна и возвращающая введенное в нем имя файла
 * */

int init_subwin(char *filename);

/*
 * Функция, открывающая файл
 * */

int file_open();

/*
 * Функция, сохраняющая файл
 * */

int file_save();


#endif