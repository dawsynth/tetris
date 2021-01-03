#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "tetrominoes.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define NUM_ACTIVE_TILES 4
#define SPEED 1

enum DIRECTION {DOWN, RIGHT, LEFT, ACCELERATED_DOWN};
enum TILE_TYPE {EMPTY = 0, INACTIVE = 1, ACTIVE = 2};

typedef struct {
    enum TILE_TYPE status[GRID_WIDTH][GRID_HEIGHT];
} Grid;

typedef struct {
    int x[NUM_ACTIVE_TILES];
    int y[NUM_ACTIVE_TILES];
    int pieceNum;
    unsigned long int pieceMoved;
} Piece;

typedef struct {
    unsigned long int time;
    unsigned int rowsCleared;
    unsigned long int score;
    unsigned int level;
    unsigned int tetrominoes[7][4][2];
    Grid *grid;
} GameData;

void gameInit(GameData *data);
void gameTerm(GameData *data);

void gameDataScoreUpdate(GameData *data, unsigned int moreRowsCleared);

int pieceInit(GameData *data, Piece *piece);
int pieceMove(GameData *data, Piece *piece, enum DIRECTION dir);
int pieceCollide(Piece *piece, Grid *grid, enum DIRECTION dir);
void pieceRotate(Piece *piece, Grid *grid);
void pieceDeactivate(Piece *piece, Grid *grid);

int gridStatusCheck(Grid *grid);
int gridClearRow(Grid *grid, int row);
int gridCheckRowEmpty(Grid *grid, int row);
void gridShiftRows(Grid *grid, int initialRow);
int gridClearRows(Grid *grid);

#endif
