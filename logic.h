#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "core.h"
#include "tetrominoes.h"

#define SPEED 1
#define NUM_ACTIVE_TILES 4
#define NUM_COLORS 3

enum DIRECTION {DOWN, RIGHT, LEFT, ACCELERATED_DOWN};

typedef struct {
    int x[NUM_ACTIVE_TILES];
    int y[NUM_ACTIVE_TILES];
    int pieceNum;
    unsigned long int pieceMoved;
} Piece;


int pieceInit(Game *game, Piece *piece);
int pieceMove(Game *game, Piece *piece, enum DIRECTION dir);
int pieceCollide(Piece *piece, Grid *grid, enum DIRECTION dir);
void pieceRotate(Piece *piece, Grid *grid);
void pieceDeactivate(Piece *piece, Grid *grid);

int gridStatusCheck(Grid *grid);
int gridClearRow(Grid *grid, int row);
int gridCheckRowEmpty(Grid *grid, int row);
void gridShiftRows(Grid *grid, int initialRow);
int gridClearRows(Grid *grid);

#endif
