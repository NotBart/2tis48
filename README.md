# 2tis48
2tis48 is a 2048 clone written in C using [raylib](https://github.com/raysan5/raylib)

This is my first actual C project, so it's horrible in every possible way. But hey, it works!
>Video: https://youtu.be/uPiteYOYonQ

## Gameplay
Use WASD or arrow keys to navigate menus and make moves in-game. Press ESC to go to the previous menu/exit.
You can also press F1 to toggle debugging information, but that probably won't be very helpful, because it just shows the game state and FPS.

## Building
You can probably build for most platforms raylib supports in any environment you want, but these are the ones I tested.
### Windows
On Windows, you can build by either:
1. Using the NppExec script "nppbuild.txt" with the [pre-packaged raylib for Windows](https://raysan5.itch.io/raylib)
	-  Open any *.c file in /src, then execute the script. You will get 2tis48.exe in the root of the repo
2. Or just use gcc (assuming it's in PATH):
```batch
cd src && gcc -o ..\2tis48.exe *.c ..\data\icon.res ..\data\exeinfo.res -s -static -O2 -std=c99 -Wall -I<PATH_TO_RAYLIB_REPO>\src -Iexternal -DPLATFORM_DESKTOP -mwindows -lraylib -lopengl32 -lgdi32 -lwinmm && cd ..
```
### Linux
Again, you can build for any concievable setup. First, you must [build raylib for Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).
#### Raspberry Pi
[Build raylib for Raspberry Pi](https://github.com/raysan5/raylib/wiki/Working-on-Raspberry-Pi) for PLATFORM_DESKTOP, then:
```bash
git clone https://github.com/NotBart/2tis48
cd 2tis48/src
gcc *.c -o ../2tis48 -I<PATH_TO_RAYLIB>/src -L<PATH_TO_RAYLIB>/src -lraylib -lm -lGL -lpthread -ldl -lrt -lX11
```

## Game algorithm
When you make a move...
1. The program stores the current game state.
2. A loop scans the game field from the opposite direction of your input for equal tile values, skipping blank tiles.
3. Matching tiles are merged, adding their cumulative value to the score.
4. All tiles are pushed to your movement direction thus eliminating gaps between them.
5. If the resulting game state is different:
	- A move is added to the counter
	- If there is at least one blank tile, a tile (either 2 or 4, with 4 falling 1/10 times) is added to a random empty space
6. If there are no blank tiles, a loop checks every tile for a matching neighbor.
	- If no tile has a matching neighbor, the game ends with the player losing.

## PVA requirements
Name: Bartoloměj Bičovský

Class: C1  (2024/25)

Grading Period: 3rd quarter

Goal: Implement a 2048 clone in C

### Steps:
- Played 2048 to learn how it works
- Implemented the basic tile merging algorithm, controls
- Added scoring, move counting
- Added main menu, help menu

All while looking at the [raylib examples](https://www.raylib.com/examples.html).

### Achievements:
- Wrote a working game
- Got a better understanding of C and raylib

### TODO:
- High-score saving
- More control methods
- Polish the game
	- add animation
	- improve visuals
- Clean up the code
- More platforms
