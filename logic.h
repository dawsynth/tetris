#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "core.h"
#include "tetrominoes.h"

#define SPEED 1
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define NUM_ACTIVE_TILES 4
#define NUM_COLORS 3

enum DIRECTION {DOWN, RIGHT, LEFT, ACCELERATED_DOWN};
enum TILE_TYPE {EMPTY = 0, INACTIVE = 1, ACTIVE = 2};

typedef struct {
    int x[NUM_ACTIVE_TILES];
    int y[NUM_ACTIVE_TILES];
    int color[3];
    int pieceNum;
    unsigned long int pieceMoved;
} Piece;

typedef struct {
    enum TILE_TYPE grid[10][20];
    int color[10][20][3];
} InactivePieces;

int pieceInit(Game *game, Piece *piece, InactivePieces *inactivePieces);
int pieceMove(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir);
int pieceCollide(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir);
void pieceRotate(Game *game, Piece *piece, InactivePieces *inactivePieces);
void pieceDeactivate(Game *game, Piece *piece, InactivePieces *inactivePieces);

int inactivePieceCheck(Game *game, InactivePieces *inactivePieces);
int inactivePieceClearRow(Game *game, InactivePieces *inactivePieces, int row);
int inactivePieceCheckRowEmpty(Game *game, InactivePieces *inactivePieces, int row);
void inactivePieceShiftRows(Game *game, InactivePieces *inactivePieces, int initialRow);
int inactivePieceClearRows(Game *game, InactivePieces *inactivePieces);

#endif
