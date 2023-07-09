enum dir { up, down, left, right };

typedef struct food {
	int x, y;
} Food;

typedef struct item {
	int x, y, dx, dy;
	enum dir cur_dir;
	bool head;
	struct item *prev, *next;
} Item;

