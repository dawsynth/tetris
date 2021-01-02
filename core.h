#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "tetrominoes.h"

#define MULTIPLIER 20
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define DEFAULT_WINDOW_WIDTH (GRID_WIDTH * MULTIPLIER)
#define DEFAULT_WINDOW_HEIGHT (GRID_HEIGHT * MULTIPLIER)

enum TILE_TYPE {EMPTY = 0, INACTIVE = 1, ACTIVE = 2};

typedef struct {
    enum TILE_TYPE status[GRID_WIDTH][GRID_HEIGHT];
} Grid;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned long int time;
    unsigned long int score;
    unsigned long int rowsCleared;
    unsigned int level;
    int w, h;
    IntVec tetrominoes[7][4];
    Grid *grid;
} Game;


void gameInit(Game *game);
void gameTerm(Game *game);
void gameScoreUpdate(Game *game, unsigned int moreRowsCleared);
#endif
