#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "logic.h"

#define MULTIPLIER 20
#define DEFAULT_WINDOW_WIDTH (GRID_WIDTH * MULTIPLIER)
#define DEFAULT_WINDOW_HEIGHT (GRID_HEIGHT * MULTIPLIER)
#define TILE_WIDTH 1 * MULTIPLIER
#define TILE_HEIGHT 1 * MULTIPLIER 

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} GraphicsPackage;

void graphicsInit(GraphicsPackage *graphics);
void graphicsTerm(GraphicsPackage *graphics);

void pieceDraw(GraphicsPackage *graphics, Piece *piece);
void gridDraw(GameData *data, GraphicsPackage *graphics);

#endif
