/*
** Filename: menu.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains functions for drawing and processing the menu.
*/

#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "include/qol.h"
#include "include/menu.h"

typedef struct {
	Color color;
	char text[3];
} MenuTile;

static Vector2 mousePos = Vec2(0.0f, 0.0f);
static ButtonStatus buttons[3] = {NORMAL, NORMAL, NORMAL};
static const Rectangle buttonPositions[3] = {{528, 212, 267, 56}, {528, 273, 267, 56}, {528, 334, 267, 56}};
static const char buttonTexts[6][16] = {"Play", "Help", "Exit", "UP", "DOWN", "ESCAPE"};
static const MenuTile menuTiles[4][4] = {{{RGBA(238, 228, 218, 255), "2"}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}},
										{{RGBA(237, 194, 46, 255), "t"}, {RGBA(237, 207, 114, 255), "i"}, {RGBA(246, 94, 59, 255), "s"}, {RGBA(204, 192, 179, 255), " "}},
										{{RGBA(237, 224, 200, 255), "4"}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}},
										{{RGBA(242, 177, 121, 255), "8"}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}, {RGBA(204, 192, 179, 255), " "}}};

void drawMenu() {
	ClearBackground(RGBA(187, 173, 160, 255));
	for (int i = 0; i < 3; i++) {
		DrawRectangleRec(buttonPositions[i], buttonColors[buttons[i]]);
		DrawTextOutline(buttonTexts[i], buttonPositions[i].x + 5, buttonPositions[i].y + 4, 20, 1, RAYWHITE, BLACK);
		DrawText(buttonTexts[i+3], buttonPositions[i].x + buttonPositions[i].width - MeasureText(buttonTexts[i+3], 10) - 2, buttonPositions[i].y + buttonPositions[i].height - 10, 10, BLACK);
	}
	
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			DrawRectangle(x * 65 + 75, y * 65 + 170, 64, 64, menuTiles[y][x].color);
			DrawTextOutline(menuTiles[y][x].text, x * 65 + 80, y * 65 + 173, 20, 1, RAYWHITE, BLACK);
		}
	}
	
	DrawText("by NotBart", 141, 300, 10, BLACK);
}

void menuLoop() {
	// buttons and key input
	mousePos = GetMousePosition();
	if ((!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && buttons[0] == CLICK) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) { gameState = 1; }
	else if ((!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && buttons[1] == CLICK) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) { gameState = 3; }
	else if ((!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && buttons[2] == CLICK)) { gameState = -1; }
	
	for (int i = 0; i < 3; i++) {
		buttons[i] = NORMAL;
		if (CheckCollisionPointRec(mousePos, buttonPositions[i])) { buttons[i] = HOVER + (int)IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
	}
}