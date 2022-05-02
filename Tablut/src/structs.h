#ifndef _structs_h
#define _structs_h


typedef struct {
	int x;
	int y;
	int prevX;
	int prevY;
	int button[MAX_MOUSE_BUTTONS];
} Mouse;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Delegate delegate;
	Mouse mouse;
} App;

typedef Uint8 Board[BOARD_LENGTH][BOARD_LENGTH];

typedef struct {
	int turn;
	int state;
} Game;

typedef struct {
	int side;
	int fromX;
	int fromY;
	int toX;
	int toY;
} Action;

#endif