#ifndef TETROMINOES_H_INCLUDED
#define TETROMINOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

typedef struct {
    int x;
    int y;
} IntVec;

void tetrominoesInit(IntVec tetrominoes[7][4]);

#endif

