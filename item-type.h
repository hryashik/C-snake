enum dir { up, down, left, right };

typedef struct item {
	int x, y, dx, dy;
	enum dir cur_dir;
	struct item *prev, *next;
} Item;

