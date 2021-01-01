#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "tetrominoes.h"


#define DEFAULT_WINDOW_WIDTH (200)
#define DEFAULT_WINDOW_HEIGHT (400)


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned long int time;
    unsigned long int score;
    unsigned long int rowsCleared;
    unsigned int level;
    int w, h;
    IntVec tetrominoes[7][4];
} Game;


void gameInit(Game *game);
void gameTerm(Game *game);
void gameScoreUpdate(Game *game, unsigned int moreRowsCleared);
#endif
