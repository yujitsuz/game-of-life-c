# Conway's Game of Life — C

Console-based Game of Life simulator built in C.

## Features
- Glider and Blinker + Block presets
- Toroidal (wraparound) borders and also Fixed
- Configurable FPS (1-60)
- Finite or infinite loop mode
- Flicker-free terminal rendering

## How to compile
gcc conwaysgame.c -o game && ./game

## What would I do next?
Since this is a simple system made for learning puporses, I believe it is in a quite stable and interesting state, but some stuff I would add:
- Scaling Matrixes defined by the user
- Values and initial positions defined by the user
- Ending the program earlier if the matrix repeats itself
