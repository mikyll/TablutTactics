#ifndef _main_h
#define _main_h


#include "common.h"

extern void cleanup();
extern void initSDL();
extern void initSDLnet();
extern void doInput();
extern SDL_Texture* loadTexture(char* filename);
extern void blit(SDL_Texture* texture, int x, int y, int center);
extern int connect(char* host, int port);
extern void receiveState(); // Test

App app;
Board gameBoard;
Game game;

#endif
