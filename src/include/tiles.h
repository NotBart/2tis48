/*
** Filename: tiles.h
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains function prototypes for spawnRandom and processMove.
*/

#ifndef TILES_H
#define TILES_H

extern int level[4][4];
extern int beforelevel[4][4];
extern int score;
extern int moves;
extern bool lost;

void spawnRandom(void);
void processMove(int side);

#endif