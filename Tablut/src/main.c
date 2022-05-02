#include "main.h"

#include <SDL2/SDL_image.h>

void initBoard();
void drawPawns();
void drawChoice();
void highlightMoves(int fromX, int fromY, SDL_Rect* rH, SDL_Rect* rV);

static SDL_Texture* textureBoard;
static SDL_Texture* texturePawnBlack;
static SDL_Texture* texturePawnWhite;
static SDL_Texture* texturePawnKing;

static int selectedX, selectedY;
static int destX, destY;

static SDL_Rect rH, rV;

int main()
{
	// check parameters: if "-g" => avvia la GUI
	initSDL();

	atexit(cleanup);

	textureBoard = loadTexture("gfx/board.png");
	texturePawnBlack = loadTexture("gfx/pawnBlack.png");
	SDL_SetTextureBlendMode(texturePawnBlack, SDL_BLENDMODE_BLEND);
	texturePawnWhite = loadTexture("gfx/pawnWhite.png");
	SDL_SetTextureBlendMode(texturePawnWhite, SDL_BLENDMODE_BLEND);
	texturePawnKing = loadTexture("gfx/pawnKing.png");
	SDL_SetTextureBlendMode(texturePawnKing, SDL_BLENDMODE_BLEND);

	SDL_Surface* srfc = IMG_Load("gfx/pawnKing.png");

	SDL_SetWindowIcon(app.window, srfc);

	initBoard();

	selectedX = -1, selectedY = -1;
	destX = -1, destY = -1;

	while (1)
	{
		app.mouse.button[MOUSE_LEFT] = 0;

		// doReceive();

		doInput();

		char buffer[64];
		sprintf(buffer, "%s %s", WINDOW_TITLE, SDL_GetTicks() % 2 == 0 ? "(WHITE turn)" : "(BLACK turn)");
		SDL_SetWindowTitle(app.window, buffer);

		prepareScene();

		if (app.mouse.button[MOUSE_LEFT])
		{
			printf("LEFT_CLICK: %d, %d\n", app.mouse.x, app.mouse.y);
			if (gameBoard[app.mouse.x / BOX_LENGTH][app.mouse.y / BOX_LENGTH] != EMPTY)
			{
				if (app.mouse.x / BOX_LENGTH == selectedX && app.mouse.y / BOX_LENGTH == selectedY)
				{
					printf("DESELECTED: %d, %d\n", selectedX, selectedY);
					selectedX = -1;
					selectedY = -1;
				}
				else
				{
					selectedX = app.mouse.x / BOX_LENGTH;
					selectedY = app.mouse.y / BOX_LENGTH;
					printf("SELECTED: %d, %d\n", selectedX, selectedY);
					highlightMoves(selectedX, selectedY, &rH, &rV);
					printf("rH: w=%d, h=%d\nrV: w=%d, h=%d\n", rH.w, rH.h, rV.w, rV.h);
				}
			}
		}
		if (selectedX != -1 && selectedY != -1 && gameBoard[app.mouse.x / BOX_LENGTH][app.mouse.y / BOX_LENGTH] == EMPTY)
		{
			destX = app.mouse.x / BOX_LENGTH;
			destY = app.mouse.y / BOX_LENGTH;
		}
		else
		{
			destX = -1;
			destY = -1;
		}
		//SDL_SetWindowTitle(app.window, WINDOW_TITLE);

		if (selectedX != -1 && selectedY != -1 && app.mouse.button[MOUSE_LEFT])
		{
			if ((app.mouse.x / BOX_LENGTH < BOARD_LENGTH && app.mouse.y / BOX_LENGTH < BOARD_LENGTH && app.mouse.x / BOX_LENGTH >= 0 && app.mouse.y / BOX_LENGTH >= 0) &&
				gameBoard[app.mouse.x / BOX_LENGTH][app.mouse.y / BOX_LENGTH] == EMPTY)
			{
				int p = gameBoard[selectedX][selectedY];
				gameBoard[selectedX][selectedY] = EMPTY;

				printf("MOVED PAWN FROM: %d, %d TO: %d, %d\n", selectedX, selectedY, app.mouse.x / BOX_LENGTH, app.mouse.y / BOX_LENGTH);
				gameBoard[app.mouse.x / BOX_LENGTH][app.mouse.y / BOX_LENGTH] = p;
				selectedX = -1;
				selectedY = -1;
			}
		}


		blit(textureBoard, 0, 0, 0);

		if (selectedX != -1 && selectedY != -1)
		{
			
			// Set render color to blue ( rect will be rendered in this color )
			SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, SDL_ALPHA_OPAQUE / 1.5);

			// Render rect
			SDL_RenderFillRect(app.renderer, &rH);
			SDL_RenderFillRect(app.renderer, &rV);
			SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
		}

		drawPawns();

		drawChoice();

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < BOARD_LENGTH; i++)
	{
		for (j = 0; j < BOARD_LENGTH; j++)
		{
			gameBoard[i][j] = EMPTY;
		}
	}

	// Black Pawns
	gameBoard[0][3] = PAWN_BLACK;
	gameBoard[0][4] = PAWN_BLACK;
	gameBoard[0][5] = PAWN_BLACK;
	gameBoard[1][4] = PAWN_BLACK;
	gameBoard[3][0] = PAWN_BLACK;
	gameBoard[3][8] = PAWN_BLACK;
	gameBoard[4][0] = PAWN_BLACK;
	gameBoard[4][1] = PAWN_BLACK;
	gameBoard[4][7] = PAWN_BLACK;
	gameBoard[4][8] = PAWN_BLACK;
	gameBoard[5][0] = PAWN_BLACK;
	gameBoard[5][8] = PAWN_BLACK;
	gameBoard[7][4] = PAWN_BLACK;
	gameBoard[8][3] = PAWN_BLACK;
	gameBoard[8][4] = PAWN_BLACK;
	gameBoard[8][5] = PAWN_BLACK;

	// White Pawns
	gameBoard[2][4] = PAWN_WHITE;
	gameBoard[3][4] = PAWN_WHITE;
	gameBoard[4][2] = PAWN_WHITE;
	gameBoard[4][3] = PAWN_WHITE;
	gameBoard[4][5] = PAWN_WHITE;
	gameBoard[4][6] = PAWN_WHITE;
	gameBoard[5][4] = PAWN_WHITE;
	gameBoard[6][4] = PAWN_WHITE;

	// King Pawn
	gameBoard[4][4] = PAWN_KING;
}

void drawPawns()
{
	SDL_Texture* t;
	int i, j;

	for (i = 0; i < BOARD_LENGTH; i++)
	{
		for (j = 0; j < BOARD_LENGTH; j++)
		{
			switch (gameBoard[i][j])
			{
			case PAWN_BLACK:
				t = texturePawnBlack;
				break;

			case PAWN_WHITE:
				t = texturePawnWhite;
				break;

			case PAWN_KING:
				t = texturePawnKing;
				break;

			default: // EMPTY
				t = NULL;
				break;
			}

			SDL_SetTextureAlphaMod(t, selectedX == i && selectedY == j ? SDL_ALPHA_OPAQUE / 1.3 : SDL_ALPHA_OPAQUE);
			blit(t, i * BOX_LENGTH + 1, j * BOX_LENGTH + 1, 0);
		}
	}
}

void drawChoice()
{
	SDL_Texture* t;

	if (destX != -1 && destY != -1)
	{
		switch (gameBoard[selectedX][selectedY])
		{
		case PAWN_BLACK:
			t = texturePawnBlack;
			break;

		case PAWN_WHITE:
			t = texturePawnWhite;
			break;

		case PAWN_KING:
			t = texturePawnKing;
			break;

		default: // EMPTY
			t = NULL;
			break;
		}

		SDL_SetTextureAlphaMod(t, SDL_ALPHA_OPAQUE / 1.3);
		blit(t, destX * BOX_LENGTH + 1, destY * BOX_LENGTH + 1, 0);
	}
}

void selectPawn(int side, int x, int y)
{

}

int checkMove(int fromX, int fromY, int toX, int toY)
{
	// Check out of board
	if (fromX < 0 || fromY < 0 || fromX >= BOARD_LENGTH || fromY >= BOARD_LENGTH || toX < 0 || toY < 0 || toX >= BOARD_LENGTH || toY >= BOARD_LENGTH)
		return EXCEPTION_BOARD;

	// Check move ends on throne
	if (toX == 4 && toY == 4)
		return EXCEPTION_THRONE;

	// Check arrival box
	if (gameBoard[toX][toY] != EMPTY)
		return EXCEPTION_OCCUPIED;
	if (toX == 0 && (toY == 3 || toY == 4 || toY == 5) ||
		toX == 1 && toY == 4 ||
		toX == 3 && (toY == 0 || toY == 8) ||
		toX == 4 && (toY == 0 || toY == 1 || toY == 7 || toY == 8) ||
		toX == 5 && (toY == 0 || toY == 8) ||
		toX == 7 && toY == 4 ||
		toX == 8 && (toY == 3 || toY == 4 || toY == 5))
		return EXCEPTION_CITADEL;

	// Check turn
	// side == game.turn
	
	return 1;
}

void highlightMoves(int fromX, int fromY, SDL_Rect* rH, SDL_Rect* rV)
{
	// Create 2 transparent Rectangles filled with yellow or another color
	SDL_Rect rHor, rVer;
	int i, j;

	rHor.x = fromX, rHor.y = fromY;
	rHor.w = 1, rHor.h = BOX_LENGTH;
	rVer.x = fromX, rVer.y = fromY;
	rVer.w = BOX_LENGTH, rVer.h = 1;

	// Horizontal
	for (i = fromX - 1, j = fromY; i >= 0; i--)
	{
		if (j == 0 && i == 5 ||
			j == 1 && i == 4 ||
			j == 3 && i == 0 ||
			j == 4 && (i == 4 || i == 1) ||
			j == 5 && i == 0 ||
			j == 7 && i == 4 ||
			j == 8 && i == 5)
			break;
		if (gameBoard[i][j] == EMPTY)
		{
			rHor.x--;
			rHor.w++;
		}
		else break;
	}
	for (i = fromX + 1, j = fromY; i < BOARD_LENGTH; i++)
	{
		if (j == 0 && i == 3 ||
			j == 1 && i == 4 ||
			j == 3 && i == 8 ||
			j == 4 && (i == 4 || i == 7) ||
			j == 5 && i == 8 ||
			j == 7 && i == 4 ||
			j == 8 && i == 3)
			break;
		if (gameBoard[i][j] == EMPTY)
		{
			//rHor.x++;
			rHor.w++;
		}
		else break;
	}
	rHor.x = rHor.x * BOX_LENGTH + 1;
	rHor.y = rHor.y * BOX_LENGTH + 1;
	rHor.w *= BOX_LENGTH;
	
	// Vertical
	for (i = fromX, j = fromY - 1; j >= 0; j--)
	{
		if (i == 0 && j == 5 ||
			i == 1 && j == 4 ||
			i == 3 && j == 0 ||
			i == 4 && (j == 4 || j == 1) ||
			i == 5 && j == 0 ||
			i == 7 && j == 4 ||
			i == 8 && j == 5)
			break;
		if (gameBoard[i][j] == EMPTY)
		{
			rVer.y--;
			rVer.h++;
		}
		else break;
	}
	for (i = fromX, j = fromY + 1; j < BOARD_LENGTH; j++)
	{
		if (i == 0 && j == 3 ||
			i == 1 && j == 4 ||
			i == 3 && j == 8 ||
			i == 4 && (j == 4 || j == 7) ||
			i == 5 && j == 8 ||
			i == 7 && j == 4 ||
			i == 8 && j == 3)
			break;
		if (gameBoard[i][j] == EMPTY)
		{
			//rVer.y++;
			rVer.h++;
		}
		else break;
	}
	rVer.x = rVer.x * BOX_LENGTH + 1;
	rVer.y = rVer.y * BOX_LENGTH + 1;
	rVer.h *= BOX_LENGTH;

	printf("rHor: x=%d, y=%d, w=%d, h=%d\nrVer: x=%d, y=%d, w=%d, h=%d\n", rHor.x, rHor.y, rHor.w, rHor.h, rVer.x, rVer.y, rVer.w, rVer.h);

	*rH = rHor;
	*rV = rVer;
}

void drawHighlight()
{

}

void drawSelectedFrom()
{

}

void drawSelectedTo()
{

}
// Timer

// Settings
// Send random move on timeout?


void selectAction()
{
	// output: 
	// se non si può spostare in quella posizione: coordinate in rosso
	// altrimenti: coordinate in verde e mostra la pedina trasparente

}