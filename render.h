#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "logic.h"

typedef struct {
    unsigned int r, g, b;
} Color;

#define MULTIPLIER 20
#define DEFAULT_WINDOW_WIDTH (GRID_WIDTH * MULTIPLIER)
#define DEFAULT_WINDOW_HEIGHT (GRID_HEIGHT * MULTIPLIER)
#define TILE_WIDTH 1 * MULTIPLIER
#define TILE_HEIGHT 1 * MULTIPLIER

#define BLACK (Color){0, 0, 0}
#define SKYBLUE (Color){102, 191, 255}
#define WHITE (Color){255, 255, 255}
#define ORANGE (Color){255, 161, 0}
#define GREEN (Color){0, 228, 48}
#define BLUE (Color){0, 121, 241}
#define PURPLE (Color){200, 122, 255}
#define BROWN (Color){127, 106, 79}
#define YELLOW (Color){253, 249, 0}
#define RED (Color){230, 41, 55}

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Color gridColors[GRID_WIDTH][GRID_HEIGHT];
} GraphicsPackage;

void graphicsInit(GraphicsPackage *graphics);
void graphicsTerm(GraphicsPackage *graphics);

void pieceDraw(GraphicsPackage *graphics, Piece *piece, int fill);
void gridDraw(GameData *data, GraphicsPackage *graphics);

#endif
