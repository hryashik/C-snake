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
	timeout(delay_duration);
	keypad(stdscr, 1);
	curs_set(0);
	noecho();
}

int main()
{
	int row, col, key;
	Item *first = malloc(sizeof(Item));
	init_game();
	getmaxyx(stdscr, row, col);
	init_snake(first, col, row);
	while((key = getch()) != key_escape) {
	/*	switch(key) {
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
				move_star(first, col, row);
				break;
		} */
		if (key == ERR) {
			move_star(first, col, row);
		} else {
			set_direction(first, key);
		}
	}
	endwin();
	return 0;
}
