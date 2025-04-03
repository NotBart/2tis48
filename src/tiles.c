/*
** Filename: tiles.c
** Author: Bartoloměj Bičovský (NotBart)
** Version: github1
** Description: Contains functions for spawning and moving tiles. This is also the worst source file in the entire project.
*/

#include <raylib.h>
#include <math.h>
#include "include/qol.h"
#include "include/tiles.h"

void spawnRandom() {
	bool hasZero = false;
	for (int y = 0; y < 4 && !hasZero; y++) {
		for (int x = 0; x < 4 && !hasZero; x++) {
			if (level[y][x] == 0) {
				hasZero = true;
			}
		}
		if (hasZero) { break; }
	}
	
	if (hasZero) {
		int spawnX = 0;
		int spawnY = 0;
		do {
			spawnX = GetRandomValue(0,3);
			spawnY = GetRandomValue(0,3);
		} while (level[spawnX][spawnY]);
		
		if (GetRandomValue(0,9) == 9) {
			level[spawnX][spawnY] = 2;
		} else {
			level[spawnX][spawnY] = 1;
		}
	}
}

// THE BELOW FUNCTION IS NOT FOR THE FAINT-OF-HEART (yes, I tried to fix it, but every time it broke, so FUN)
void processMove(int side) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			beforelevel[y][x] = level[y][x];
		}
	}
	
	switch (side) {
		case 1: // right
			for (int moveRow = 0; moveRow < 4; moveRow++) {
				for (int moveCol = 3; moveCol >= 0; moveCol--) {
					if (level[moveRow][moveCol]) {
						for (int moveColN = moveCol-1; moveColN >= 0; moveColN--) {
							if (level[moveRow][moveColN]) {
								if (level[moveRow][moveCol] == level[moveRow][moveColN]) {
									level[moveRow][moveCol] += 1;
									level[moveRow][moveColN] = 0;
									score += (int)pow(2, level[moveRow][moveCol]);
								}
								break;
							}
						}
					}
				}
			}
			break;
		case 2: // left
			for (int moveRow = 0; moveRow < 4; moveRow++) {
				for (int moveCol = 0; moveCol < 4; moveCol++) {
					if (level[moveRow][moveCol]) {
						for (int moveColN = moveCol+1; moveColN < 4; moveColN++) {
							if (level[moveRow][moveColN]) {
								if (level[moveRow][moveCol] == level[moveRow][moveColN]) {
									level[moveRow][moveCol] += 1;
									level[moveRow][moveColN] = 0;
									score += (int)pow(2, level[moveRow][moveCol]);
								}
								break;
							}
						}
					}
				}
			}
			break;
		case 3: // up
			for (int moveCol = 0; moveCol < 4; moveCol++) {
				for (int moveRow = 0; moveRow < 4; moveRow++) {
					if (level[moveRow][moveCol]) {
						for (int moveRowN = moveRow+1; moveRowN < 4; moveRowN++) {
							if (level[moveRowN][moveCol]) {
								if (level[moveRow][moveCol] == level[moveRowN][moveCol]) {
									level[moveRow][moveCol] += 1;
									level[moveRowN][moveCol] = 0;
									score += (int)pow(2, level[moveRow][moveCol]);
								}
								break;
							}
						}
					}
				}
			}
			break;
		case 4: // down
			for (int moveCol = 0; moveCol < 4; moveCol++) {
				for (int moveRow = 3; moveRow >= 0; moveRow--) {
					if (level[moveRow][moveCol]) {
						for (int moveRowN = moveRow-1; moveRowN >= 0; moveRowN--) {
							if (level[moveRowN][moveCol]) {
								if (level[moveRow][moveCol] == level[moveRowN][moveCol]) {
									level[moveRow][moveCol] += 1;
									level[moveRowN][moveCol] = 0;
									score += (int)pow(2, level[moveRow][moveCol]);
								}
								break;
							}
						}
					}
				}
			}
			break;
	}
	
	switch (side) {
		case 1: // right
			for (int unzeroRow = 0; unzeroRow < 4; unzeroRow++) {
				int unzeroTbl[4] = {0,0,0,0};
				int unzeroCount = 0;
				for (int unzeroCol = 0; unzeroCol < 4; unzeroCol++) {
					if (level[unzeroRow][unzeroCol]) {
						unzeroTbl[unzeroCount] = level[unzeroRow][unzeroCol];
						unzeroCount++;
					}
				}
				if (unzeroCount == 0) { continue; }
				level[unzeroRow][0] = 0;
				level[unzeroRow][1] = 0;
				level[unzeroRow][2] = 0;
				level[unzeroRow][3] = 0;
				for (int i = 3; i >= 0; i--) {
					level[unzeroRow][i] = unzeroTbl[unzeroCount-1];
					unzeroCount--;
					if (unzeroCount == 0) { break; }
				}
			}
			break;
		case 2: // left
			for (int unzeroRow = 0; unzeroRow < 4; unzeroRow++) {
				int unzeroTbl[4] = {0,0,0,0};
				int unzeroCount = 0;
				for (int unzeroCol = 0; unzeroCol < 4; unzeroCol++) {
					if (level[unzeroRow][unzeroCol]) {
						unzeroTbl[unzeroCount] = level[unzeroRow][unzeroCol];
						unzeroCount++;
					}
				}
				if (unzeroCount == 0) { continue; }
				level[unzeroRow][0] = 0;
				level[unzeroRow][1] = 0;
				level[unzeroRow][2] = 0;
				level[unzeroRow][3] = 0;
				for (int i = 0; i < 4; i++) {
					level[unzeroRow][i] = unzeroTbl[i];
				}
			}
			break;
		case 3: // up
			for (int unzeroCol = 0; unzeroCol < 4; unzeroCol++) {
				int unzeroTbl[4] = {0,0,0,0};
				int unzeroCount = 0;
				for (int unzeroRow = 0; unzeroRow < 4; unzeroRow++) {
					if (level[unzeroRow][unzeroCol]) {
						unzeroTbl[unzeroCount] = level[unzeroRow][unzeroCol];
						unzeroCount++;
					}
				}
				if (unzeroCount == 0) { continue; }
				level[0][unzeroCol] = 0;
				level[1][unzeroCol] = 0;
				level[2][unzeroCol] = 0;
				level[3][unzeroCol] = 0;
				for (int i = 0; i < 4; i++) {
					level[i][unzeroCol] = unzeroTbl[i];
				}
			}
			break;
		case 4: // down
			for (int unzeroCol = 0; unzeroCol < 4; unzeroCol++) {
				int unzeroTbl[4] = {0,0,0,0};
				int unzeroCount = 0;
				for (int unzeroRow = 0; unzeroRow < 4; unzeroRow++) {
					if (level[unzeroRow][unzeroCol]) {
						unzeroTbl[unzeroCount] = level[unzeroRow][unzeroCol];
						unzeroCount++;
					}
				}
				if (unzeroCount == 0) { continue; }
				level[0][unzeroCol] = 0;
				level[1][unzeroCol] = 0;
				level[2][unzeroCol] = 0;
				level[3][unzeroCol] = 0;
				for (int i = 3; i >= 0; i--) {
					level[i][unzeroCol] = unzeroTbl[unzeroCount-1];
					unzeroCount--;
					if (unzeroCount == 0) { break; }
				}
			}
			break;
	}
	
	bool isDifferent = false;
	for (int y = 0; y < 4 && !isDifferent; y++) {
		for (int x = 0; x < 4 && !isDifferent; x++) {
			if (beforelevel[y][x] != level[y][x]) { isDifferent = true; }
		}
	}

	if (isDifferent) { spawnRandom(); moves++; }
	
	bool hasZero = false;
	for (int y = 0; y < 4 && !hasZero; y++) {
		for (int x = 0; x < 4 && !hasZero; x++) {
			if (level[y][x] == 0) {
				hasZero = true;
			}
		}
	}

	lost = true;
	if (!hasZero) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if ((level[y][x] == level[y][x+1] && x < 3) || (level[y][x] == level[y+1][x] && y < 3)) {
					lost = false;
				}
			}
		}
	} else {
		lost = false;
	}
}