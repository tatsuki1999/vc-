#pragma once

#include "stdafx.h"
#include"windows.h"
#include <conio.h>

//É}ÉNÉçêÈåæ
#define BUFFSIZE 1024

static const int BOARD_WIDTH = 8;
static const int BOARD_HEIGHT = 8;

//ç\ë¢ëÃêÈåæ
struct  Boad {

	int Othello_WIDTH;
	int Othello_HEIGHT;

};

enum
{
	COLOR_NONE = -1,
	COLOR_BLACK = 0,
	COLOR_WHITE = 1,
	COLOR_MAX
};

enum
{
	DIRECTION_UP,
	DIRECTION_UP_LEFT,
	DIRECTION_LEFT,
	DIRECTION_DOWN_LEFT,
	DIRECTION_DOWN,
	DIRECTION_DOWN_RIGHT,
	DIRECTION_RIGHT,
	DIRECTION_UP_RIGHT,
	DIRECTION_MAX
};

char colorNames[][5 + 1] =
{
	"Black",
	"White"
};

int directions[][2] =
{
	{ 0, -1 },
	{ -1, -1 },
	{ -1, 0 },
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
	{ 1, -1 },
};


int cells[BOARD_HEIGHT][BOARD_WIDTH];

int cursorX;
int cursorY;

int turn;

void display();
bool checkCanPut(int argColor, int argCursorX, int argCursorY, bool turnOver);
bool checkCanPutAll(int argColor);
