#ifndef _main_h
#define _main_h


#include "common.h"

extern void cleanup();
extern void initSDL();
extern void doInput();
extern SDL_Texture* loadTexture(char* filename);
extern void blit(SDL_Texture* texture, int x, int y, int center);

App app;
Board gameBoard;
Game game;

#endif
