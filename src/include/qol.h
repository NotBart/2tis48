/*
** Filename: qol.h
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Header containing quality-of-life macros, the ButtonStatus enum, button colors and the DrawTextOutline function prototype.
*/

#ifndef QOL_H
#define QOL_H

#define RGBA(r, g, b, a) (Color){r, g, b, a}
#define Vec2(x, y) (Vector2){x, y}

typedef enum {
	NORMAL,
	HOVER,
	CLICK
} ButtonStatus;
static const Color buttonColors[3] = {RGBA(204, 192, 179, 255), RGBA(238, 228, 218, 255), RGBA(237, 207, 114, 255)};

void DrawTextOutline(const char *text, int posX, int posY, int fontSize, int outlineSize, Color color, Color outlineColor);

#endif