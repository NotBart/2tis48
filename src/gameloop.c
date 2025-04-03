/*
** Filename: gameloop.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains functions for drawing and processing the actual gameplay.
*/

#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "include/qol.h"
#include "include/tiles.h"
#include "include/gameloop.h"

Color colors[12] = {RGBA(204, 192, 179, 255), RGBA(238, 228, 218, 255), RGBA(237, 224, 200, 255), RGBA(242, 177, 121, 255), RGBA(245, 149, 99, 255), RGBA(246, 124, 95, 255), RGBA(246, 94, 59, 255), RGBA(237, 207, 114, 255), RGBA(237, 204, 97, 255), RGBA(237, 200, 80, 255), RGBA(237, 197, 63, 255), RGBA(237, 194, 46, 255)};
static int moveDirection = 0;
static char moveString[16];
static char scoreString[16];
static char tileString[16];
static ButtonStatus menuButton = NORMAL;
static ButtonStatus retryButton = NORMAL;
static Vector2 mousePos = {0.0f, 0.0f};

int level[4][4];
int beforelevel[4][4];
int moves = 0;
int score = 0;
bool lost = false;

void initGame() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			beforelevel[y][x] = 0;
			level[y][x] = 0;
		}
	}
	moves = 0;
	score = 0;
	lost = false;
	spawnRandom();
	spawnRandom();
}

void drawGame() {
	ClearBackground(RGBA(237, 224, 200, 255));
	DrawRectangle(264, 164, 271, 271, RGBA(187, 173, 160, 255)); 	// tile background
	DrawRectangle(229, 164, 30, 30, buttonColors[menuButton]);		// exit button
	DrawText("ESC", 237, 184, 10, BLACK);
	
	if (lost) {
		DrawTextOutline("You lost.", 295, 445, 20, 1, RAYWHITE, BLACK);
		DrawRectangle(440, 443, 65, 26, buttonColors[retryButton]);
		DrawTextOutline("Retry", 443, 445, 20, 1, RAYWHITE, BLACK);
	}
	
	// move counter
	sprintf(moveString, "%d", moves);
	DrawRectangle(540, 267, 90, 30, RGBA(187, 173, 160, 255));
	DrawText("Moves", 542, 268, 10, BLACK);
	DrawTextOutline(moveString, 626 - MeasureText(moveString, 20), 277, 20, 1, RAYWHITE, BLACK);
	
	// score counter
	sprintf(scoreString, "%d", score);
	DrawRectangle(540, 302, 90, 30, RGBA(187, 173, 160, 255));
	DrawText("Score", 542, 303, 10, BLACK);
	DrawTextOutline(scoreString, 626 - MeasureText(scoreString, 20), 312, 20, 1, RAYWHITE, BLACK);
	
	// tiles
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			DrawRectangle(x * 65 + 270, y * 65 + 170, 64, 64, colors[level[y][x]]);
			if (level[y][x] != 0) {
				sprintf(tileString, "%d", (int)pow(2, level[y][x]));
				DrawTextOutline(tileString, x * 65 + 275, y * 65 + 173, 20, 1, RAYWHITE, BLACK);
			}
		}
	}
}
 
void gameLoop() {
	mousePos = GetMousePosition();
	
	// move controls
	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) { moveDirection = 1; }
	else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) { moveDirection = 2; }
	else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) { moveDirection = 3; }
	else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) { moveDirection = 4; }
	if (moveDirection) { processMove(moveDirection); }
	moveDirection = 0;
	
	// exit button
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && menuButton == CLICK) { gameState = 0; }
	menuButton = NORMAL;
	if (CheckCollisionPointRec(mousePos, (Rectangle){229, 164, 30, 30})) { menuButton = HOVER + (int)IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
	
	// retry button
	if (((!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && retryButton == CLICK) || IsKeyPressed(KEY_R)) && lost) { gameState = 1; }
	retryButton = NORMAL;
	if (CheckCollisionPointRec(mousePos, (Rectangle){440, 443, 65, 26})) { retryButton = HOVER + (int)IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
}