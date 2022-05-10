#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

void doKeyDown(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

void doMouseButtonUp(SDL_MouseButtonEvent* event)
{
	app.mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent* event)
{
	app.mouse.button[event->button] = 1;
}

void doMouseWheel(SDL_MouseWheelEvent* event)
{
	if (event->y > 0)
	{
		app.mouse.wheelUp = 1;
	}
	if (event->y < 0)
	{
		app.mouse.wheelDown = 1;
	}
}

void doInput()
{
	SDL_Event event;

	app.mouse.wheelUp = 0;
	app.mouse.wheelDown = 0;

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

		case SDL_MOUSEWHEEL:
			doMouseWheel(&event.wheel);
			break;

		default:
			break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}