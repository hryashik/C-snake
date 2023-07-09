#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "item-type.h"
#include "snake.h"

enum { delay_duration = 100 };
enum { key_escape = 27 };

void init_game()
{
	initscr();
	cbreak();
	keypad(stdscr, 1);
	curs_set(0);
	noecho();
}

int main()
{
	int row, col, key;
	Item *first = malloc(sizeof(Item));
	initscr();
	cbreak();
	timeout(delay_duration);
	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	getmaxyx(stdscr, row, col);
	first->x = col/2;
	first->y = row/2;
	set_direction(first, 0, 0);
	while((key = getch()) != key_escape) {
		switch(key) {
			case KEY_UP:
				set_direction(first, 0, -1);
				break;
			case KEY_DOWN:
				set_direction(first, 0, 1);
				break;
			case KEY_LEFT:
				set_direction(first, -1, 0);
				break;
			case KEY_RIGHT:
				set_direction(first, 1, 0);
				break;
			case ERR:
				move_star(first);
				break;
		}
	}
	endwin();
	return 0;
}
