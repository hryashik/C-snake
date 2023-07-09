#include <stdio.h>
#include "types.h"
#include <ncurses.h>
#include <stdlib.h>

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
Item* add_item(Item *first, Item *last)
{
	Item *tmp;
	tmp = malloc(sizeof(Item));
	tmp->x = last->x - last->dx;
	tmp->y = last->y - last->dy;
	tmp->prev = last;
	tmp->next = NULL;
	last->next = tmp;
	return tmp;
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
			if(ptr->cur_dir != down) {	
				ptr->dx = 0;
				ptr->dy = -1;
				ptr->cur_dir = up;
			}
			break;
		case KEY_DOWN:
			if(ptr->cur_dir != up) {
				ptr->dx = 0;
				ptr->dy = 1;
				ptr->cur_dir = down;
			}
			break;
		case KEY_LEFT:
			if(ptr->cur_dir != right) {
				ptr->dx = -1;
				ptr->dy = 0;
				ptr->cur_dir = left;
			}
			break;
		case KEY_RIGHT:
			if(ptr->cur_dir != left) {
				ptr->dx = 1;
				ptr->dy = 0;
				ptr->cur_dir = right;
			}
			break;
	}
	
	//ptr->dx = x;
	//ptr->dy = y;
}

void move_star(Item *ptr, bool *status, int max_x, int max_y)
{
	hide_star(ptr);
	ptr->x += ptr->dx;
	ptr->y += ptr->dy;
	if (ptr->x > (max_x - 2) || ptr->x < 1) {	
		*status = false;
		return;
	} else if (ptr->y > (max_y - 2) || ptr->y < 2) {
		*status = false;
		return;
	}
	draw_star(ptr);
}
