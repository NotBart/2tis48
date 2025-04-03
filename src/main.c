/*
** Filename: main.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains main entry function which constantly processes the game.
*/

#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "include/qol.h"
#include "include/tiles.h"
#include "include/gameloop.h"
#include "include/menu.h"
#include "include/help.h"

int gameState = 0;
int renderState = 0;
bool showDebug = 0;

int main() {
	InitWindow(800, 600, "2tis48");
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);
	char statusstring[16] = "STATE  ";
	
	while (gameState != -1 && !WindowShouldClose()) {
		if (IsKeyPressed(KEY_ESCAPE)) { gameState = (gameState == 0) ? -1 : 0; } // set gamestate to -1 if it is 0 otherwise 0
		if (IsKeyPressed(KEY_F1)) { showDebug = !showDebug; }
		
		renderState = gameState;
		switch (gameState) {
			case 0: // process the menu
				menuLoop();
				break;
			case 1: // game initalization
				initGame();
				gameState = 2;
				break;
			case 2: // main game loop
				gameLoop();
				break;
			case 3: // process the help screen
				helpLoop();
				break;
		}
				
		BeginDrawing();
			switch (renderState) {
				case 0: // draw menu
					drawMenu();
					break;
				case 2: // draw game
					drawGame();
					break;
				case 3: // draw help
					drawHelp();
					break;
			}
			if (showDebug) {
				statusstring[7] = '0' + gameState;
				statusstring[8] = '0' + renderState;
				statusstring[9] = '\0';
				DrawText(statusstring, 600, 560, 20, RGBA(255,0,0,255));
				DrawFPS(720, 580);
			}
		EndDrawing();
	}
	
	CloseWindow();
	
	return EXIT_SUCCESS;
}