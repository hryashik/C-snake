#include <stdio.h>
#include <stdbool.h>
#include "types.h"
#include <ncurses.h>
#include <stdlib.h>

static void draw_star(Item *first)
{
	if (first) {	
		char sn_char = '*';
		move(first->y, first->x);
		if(first->head) {
			attrset(COLOR_PAIR(1));
			addch(sn_char | A_BOLD);
			attrset(COLOR_PAIR(0));
		} else {
			attrset(COLOR_PAIR(2));
			addch(sn_char | A_BOLD);
			attrset(COLOR_PAIR(0));
		}
		refresh();
		draw_star(first->next);
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
	first->head = true;
	first->cur_dir = left;
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
}

static bool check(Item *f, int x, int y)
{
	while(f) {	
		if(f->x == x && f->y == y)
			return false;
		f = f->next;
	}
	return true;
}

void move_star(Item *ptr, bool *status, int max_x, int max_y)
{
	if(ptr) {
		hide_star(ptr);
		if(ptr->head) {
			ptr->x += ptr->dx;
			ptr->y += ptr->dy;
			if(!check(ptr->next, ptr->x, ptr->y)) {
				*status = false;
				return;
			}
			if (ptr->x > (max_x - 2) || ptr->x < 1) {	
				*status = false;
				return;
			} else if (ptr->y > (max_y - 2) || ptr->y < 2) {
				*status = false;
				return;
			}
		} else {
			ptr->x = ptr->prev->x;
			ptr->y = ptr->prev->y;
		}
		move_star(ptr->prev, status, max_x, max_y);
		draw_star(ptr);
	}
}
