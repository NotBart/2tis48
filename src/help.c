/*
** Filename: help.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains functions for drawing and processing the help screen.
*/

#include <raylib.h>
#include "include/qol.h"
#include "include/help.h"

static Vector2 mousePos = Vec2(0.0f, 0.0f);
static ButtonStatus backButton = NORMAL;

void drawHelp() {
	ClearBackground(RGBA(187, 173, 160, 255));
	DrawRectangleRec((Rectangle){528, 539, 267, 56}, buttonColors[backButton]);
	DrawTextOutline("Back", 533, 543, 20, 1, RAYWHITE, BLACK);
	DrawTextOutline("Use WASD or arrows to move all tiles to that side.\nPress ESC at any time to go back to the previous screen.\n\nThere is no limit to the highest tile.\nThere are also no undos, so good luck.", 80, 60, 20, 1, RAYWHITE, BLACK);
	DrawText("ESCAPE", 752, 585, 10, BLACK);
}

void helpLoop() {
	mousePos = GetMousePosition();
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && backButton == CLICK) { gameState = 0; }

	backButton = NORMAL;
	if (CheckCollisionPointRec(mousePos, (Rectangle){528, 539, 267, 56})) { backButton = HOVER + (int)IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
}