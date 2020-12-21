#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "tetrominoes.h"

#define SPEED 1


typedef struct {
    SDL_Rect tetromino[4];
    int color[3];
    int pieceNum;
    unsigned long int pieceMoved;
} Piece;

typedef struct {
    int grid[10][20];
    int color[10][20][3];
} InactivePieces;

enum DIRECTION {DOWN, RIGHT, LEFT, ACCELERATED_DOWN};

void pieceInit(Game *game, Piece *piece);
void pieceDraw(Game *game, Piece *piece);
void pieceMove(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir);
int pieceCollide(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir);
void pieceRotate(Game *game, Piece *piece, InactivePieces *inactivePieces);
void pieceDeactivate(Game *game, Piece *piece, InactivePieces *inactivePieces);
void inactivePieceDraw(Game *game, InactivePieces *inactivePieces);
int inactivePieceCheck(Game *game, InactivePieces *inactivePieces);
int inactivePieceClearRow(Game *game, InactivePieces *inactivePieces, int row);
int inactivePieceCheckRowEmpty(Game *game, InactivePieces *inactivePieces, int row);
void inactivePieceShiftRows(Game *game, InactivePieces *inactivePieces, int initialRow);
void inactivePieceClearRows(Game *game, InactivePieces *inactivePieces);

#endif
