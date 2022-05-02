#include "init.h"

void initSDL()
{
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	// init SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Couldn't initialize SDL: %s", SDL_GetError());
		exit(1);
	}

	if (!(app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags)))
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to open% d x% d window : % s\n", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	if (!(app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags)))
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	// Init SDL Image
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Couldn't initialize SDLImage: %s\n", SDL_GetError());
		exit(1);
	}
}

void cleanup()
{
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	SDL_Quit();
}