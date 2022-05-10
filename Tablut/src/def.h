#ifndef _def_h
#define _def_h


#define WINDOW_TITLE			"Tablut"

#define WINDOW_WIDTH			464
#define WINDOW_HEIGHT			464

#define MAX_KEYBOARD_KEYS        350

#define BOX_LENGTH				48

#define MAX_MOUSE_BUTTONS		6
#define MOUSE_LEFT				1
#define MOUSE_RIGHT				3


#define BOARD_LENGTH			9

#define EMPTY					0
#define PAWN_BLACK				1
#define PAWN_WHITE				2
#define PAWN_KING				3

#define DEFAULT_ADDRESS			"127.0.0.1"
#define PORT_WHITE				5800
#define PORT_BLACK				5801

enum Exception {
	EXCEPTION_BOARD = -1,
	EXCEPTION_THRONE = -2,
	EXCEPTION_OCCUPIED = -3,
	EXCEPTION_CITADEL = -4,
	EXCEPTION_STOP = -5,
};


#endif
