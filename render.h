#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "tetrominoes.h"


#define DEFAULT_WINDOW_WIDTH (100)
#define DEFAULT_WINDOW_HEIGHT (200)


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned long int time;
    int w, h;
    SDL_Rect tetrominoes[7][4];
} Game;


void gameInit(Game *game);
void gameTerm(Game *game);
#endif
