#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "types.h"
#include "snake.h"
#include <time.h>

enum { delay_duration = 100 };
enum { key_escape = 27 };

void show_score(int n) {
	char message[] = "Score: ";
	move(0, 10);
	attrset(COLOR_PAIR(1) | A_BOLD);
	addstr(message);
	attrset(COLOR_PAIR(0));
	printw("%d", n);
}

void draw_walls(int max_x, int max_y)
{
	int x, y, i;
	i = 0;
	attrset(COLOR_PAIR(4) | A_BOLD);
	while(i < max_x) {
		move(1, i);
		addch('-');
		i++;
	}
	i = 0;
	while(i < max_x) {
		move(max_y - 1, i);
		addch('-');
		i++;
	}
	i = 1;
	while(i < max_y - 1) {
		move(i, 0);
		addch('|');
		i++;
	}
	i = 1;
	while(i < max_y - 1) {
		move(i, max_x - 1);
		addch('|');
		i++;
	}
	attrset(COLOR_PAIR(0));
}

void hide_food(Food *f) 
{
	move(f->y, f->x);
	addch(' ');
	refresh();
}

void gen_food(Food *f, int max_x, int max_y) {
	if(f->x && f->y)
		hide_food(f);
	char sym = '@';
	int x = rand() % (max_x - 2);
	int y = rand() % (max_y - 2);
	f->x = x + 1;
	f->y = y + 2;
	move(f->y, f->x);
	attrset(COLOR_PAIR(3) | A_BOLD);
	addch(sym);
	attrset(COLOR_PAIR(0));
	refresh();
}

void init_game()
{
	srand(time(NULL));
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	cbreak();
	timeout(delay_duration);
	keypad(stdscr, 1);
	curs_set(0);
	noecho();
}
static void add_item(Item *f, Item *l)
{
	Item *tmp;
	tmp = malloc(sizeof(Item));
	tmp->x = l->x - l->dx;
	tmp->y = l->y - l->dy;
	tmp->cur_dir = l->cur_dir;
	tmp->dx = l->dx;
	tmp->dy = l->dy;
	tmp->prev = l;
	tmp->next = NULL;
	l->next = tmp;
}
int main()
{
	int row, col, key, score;
	score = 0;
	bool status = true;
	Item *first = malloc(sizeof(Item));
	Item *last = first;
	Food *f = malloc(sizeof(Food));
	init_game();
	show_score(score);
	getmaxyx(stdscr, row, col);
	draw_walls(col, row);
	gen_food(f, col, row);
	init_snake(first, col, row);
	while((key = getch()) != key_escape) {
		if(f->x == first->x && f->y == first->y) {
			score++;
			show_score(score);
			gen_food(f, col, row);
			add_item(first, last);
			last = last->next;
		}
		if(!status) {
			break;
		}
		
		if (key == ERR) {
			move_star(last, &status, col, row);
		} else {
			set_direction(first, key);
		}
	}
	endwin();
	return 0;
}
