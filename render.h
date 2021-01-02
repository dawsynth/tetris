#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "core.h"
#include "logic.h"

void pieceDraw(Game *game, Piece *piece);
void gridDraw(Game *game);

#endif
