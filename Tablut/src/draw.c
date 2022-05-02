#include "draw.h"

void prepareScene()
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(app.renderer);
}

void presentScene()
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTexture(char* filename)
{
	SDL_Texture* texture;

	if (!(texture = IMG_LoadTexture(app.renderer, filename)))
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Loading of texture '%s' failed", filename);
		exit(1);
	}
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loaded texture '%s'", filename);

	return texture;
}

void blit(SDL_Texture* texture, int x, int y, int center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= (dest.w / 2);
		dest.y -= (dest.h / 2);
	}

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitScaled(SDL_Texture* texture, int x, int y, float sx, float sy)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	if (sx > 0.0 && sy > 0.0)
	{
		dest.w = (int)(dest.w * sx);
		dest.h = (int)(dest.h * sy);
	}

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRotated(SDL_Texture* texture, int x, int y, int center, float angle)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= (dest.w / 2);
		dest.y -= (dest.h / 2);
	}

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void blitScaledRotated(SDL_Texture* texture, int x, int y, float sx, float sy, float angle)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	if (sx > 0.0 && sy > 0.0)
	{
		dest.w = (int)(dest.w * sx);
		dest.h = (int)(dest.h * sy);
	}

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}