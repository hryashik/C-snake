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

void init_snake(Item *first,int max_x, int max_y)
{
	first->x = max_x/2;
	first->y = max_y/2;
	first->dx = -1;
	first->dy = 0;
	first->prev = NULL;
	first->next = NULL;
	first->cur_dir = left;
	draw_star(first);
}

void set_direction(Item *ptr, int key)
{
	switch(key) {
		case KEY_UP:
			ptr->dx = 0;
			ptr->dy = -1;
			break;
		case KEY_DOWN:
			ptr->dx = 0;
			ptr->dy = 1;
			break;
		case KEY_LEFT:
			ptr->dx = -1;
			ptr->dy = 0;
			break;
		case KEY_RIGHT:
			ptr->dx = 1;
			ptr->dy = 0;
			break;
	}
	//ptr->dx = x;
	//ptr->dy = y;
}

void move_star(Item *ptr, int max_x, int max_y)
{
	hide_star(ptr);
	ptr->x += ptr->dx;
	ptr->y += ptr->dy;
	draw_star(ptr);
}
