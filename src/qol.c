/*
** Filename: qol.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains the DrawTextOutline function.
*/

#include <raylib.h>
#include "include/qol.h"

void DrawTextOutline(const char *text, int posX, int posY, int fontSize, int outlineSize, Color color, Color outlineColor) {
	DrawText(text, posX + outlineSize, posY + outlineSize, fontSize, outlineColor);
	DrawText(text, posX - outlineSize, posY - outlineSize, fontSize, outlineColor);
	DrawText(text, posX - outlineSize, posY + outlineSize, fontSize, outlineColor);
	DrawText(text, posX + outlineSize, posY - outlineSize, fontSize, outlineColor);
	DrawText(text, posX, posY, fontSize, color);
}