#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event)
{
	/*if (event->repeat == 0)
	{
		if (event->keysym.sym == SDLK_s) // event->keysym.scancode == SDL_SCANCODE_DOWN
		{
			app.susDetected = 0;
		}
	}*/
}

void doKeyDown(SDL_KeyboardEvent* event)
{
	/*if (event->repeat == 0)
	{
		if (event->keysym.sym == SDLK_s) // event->keysym.scancode == SDL_SCANCODE_DOWN
		{
			app.susDetected = 1;
		}
	}*/
}

void doMouseButtonUp(SDL_MouseButtonEvent* event)
{
	app.mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent* event)
{
	app.mouse.button[event->button] = 1;
}

void doInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			doKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			doKeyUp(&event.key);
			break;

		case SDL_MOUSEBUTTONDOWN:
			doMouseButtonDown(&event.button);
			break;

		case SDL_MOUSEBUTTONUP:
			doMouseButtonUp(&event.button);
			break;

		default:
			break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}