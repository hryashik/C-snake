#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "item-type.h"
#include "snake.h"

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
	Item *first = malloc(sizeof(Item));
	char key;
	initscr();
	cbreak();
	timeout(100);
	keypad(stdscr, 1);
	init_snake(first);
	noecho();
	curs_set(0);
	while((key = getch() != key_escape)) {
		switch(key) {
			case ERR:
				move_star(first);
				break;
		}
	}
	refresh();
	endwin();
	return 0;
}
