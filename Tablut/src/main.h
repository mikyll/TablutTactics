#ifndef _main_h
#define _main_h


#include "common.h"

extern void cleanup();
extern void initSDL();
extern void doInput();
extern SDL_Texture* loadTexture(char* filename);
extern void presentScene();
extern void presentScene();
extern void blit(SDL_Texture* texture, int x, int y, int center);

App app;
Board gameBoard;
Board savedBoards[MAX_SAVED_BOARDS];


#endif