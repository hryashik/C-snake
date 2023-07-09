#include <stdio.h>
#include "item-type.h"
#include <ncurses.h>

static void draw_star(Item *first)
{
	if (first) {	
		char sn_char = '*';
		move(first->y, first->x);
		addch(sn_char);
		refresh();
	}
}

static void hide_star(Item *ptr)
{
	move(ptr->y, ptr->x);
	addch(' ');
	refresh();
}

void init_snake(Item *first)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	first->x = x/2;
	first->y = y/2;
	first->dx = -1;
	first->dy = 0;
	first->prev = NULL;
	first->next = NULL;
	draw_star(first);
}

void set_direction(Item *ptr, int x, int y)
{
	ptr->dx = x;
	ptr->dy = y;
}

void move_star(Item *ptr)
{
	hide_star(ptr);
	ptr->x += ptr->dx;
	ptr->y += ptr->dy;
	addstr("sd");
	draw_star(ptr);
}
