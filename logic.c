#include "logic.h"

int pieceInit(Game *game, Piece *piece, InactivePieces *inactivePieces)
{
    int i;
    for (i = 0; i < NUM_COLORS; i++)
    {
        piece->color[i] = rand() % 256;
    }
    piece->pieceNum = rand() % 7;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        piece->x[i] = game->tetrominoes[piece->pieceNum][i].x;
        piece->y[i] = game->tetrominoes[piece->pieceNum][i].y;
        if (inactivePieces->grid[piece->x[i]][piece->y[i]] == INACTIVE) return -1;
    }
    if (game->time <= 0) piece->pieceMoved = 0;
    return 0;
}

int pieceMove(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir)
{
    switch(dir)
    {
        case RIGHT:
            if (!(pieceCollide(game, piece, inactivePieces, dir))) {
                piece->x[0] += SPEED;
                piece->x[1] += SPEED;
                piece->x[2] += SPEED;
                piece->x[3] += SPEED;
            }
            break;
        case LEFT:
            if (!(pieceCollide(game, piece, inactivePieces, dir))) { 
                piece->x[0] -= SPEED;
                piece->x[1] -= SPEED;
                piece->x[2] -= SPEED;
                piece->x[3] -= SPEED;
            }
            break;
        case ACCELERATED_DOWN:
            if (!(pieceCollide(game, piece, inactivePieces, dir))) {
                piece->y[0] += SPEED;
                piece->y[1] += SPEED;
                piece->y[2] += SPEED;
                piece->y[3] += SPEED;
                piece->pieceMoved = game->time;
            }
            break;
        case DOWN:
        default:
            if (!(pieceCollide(game, piece, inactivePieces, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (game->level * 5))  <= game->time)) {
                piece->y[0] += SPEED;
                piece->y[1] += SPEED;
                piece->y[2] += SPEED;
                piece->y[3] += SPEED;
                piece->pieceMoved = game->time; 
            }
            else if ((pieceCollide(game, piece, inactivePieces, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (game->level * 5)) <= game->time)) {
                pieceDeactivate(game, piece, inactivePieces);
                unsigned int rowsCleared = inactivePieceClearRows(game, inactivePieces);
                gameScoreUpdate(game, rowsCleared);
                if (pieceInit(game, piece, inactivePieces) != 0) return -1;
            }
            break;
    }
    return 0;
}

int pieceCollide(Game *game, Piece *piece, InactivePieces *inactivePieces, enum DIRECTION dir)
{
    int i;
    switch (dir)
    {
        case RIGHT:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->x[i] + 1 >= GRID_WIDTH) return 1;
                else if (inactivePieces->grid[piece->x[i] + 1][piece->y[i]] == INACTIVE) return 1;
            }
            break;
        case LEFT:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->x[i] == 0) return 1;
                else if (inactivePieces->grid[piece->x[i] - 1][piece->y[i]] == INACTIVE) return 1;
            }
            break;
        case ACCELERATED_DOWN:
        case DOWN:
        default:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->y[i] + 1 >= GRID_HEIGHT) return 1;
                else if (inactivePieces->grid[piece->x[i]][piece->y[i] + 1] == INACTIVE) return 1;
            }
            break;
    }
    return 0;
}

void pieceRotate(Game *game, Piece *piece, InactivePieces *inactivePieces)
{
    int i;
    int xPrime[NUM_ACTIVE_TILES], yPrime[NUM_ACTIVE_TILES];
    int originPiece;
    switch(piece->pieceNum)
    {
        case 0:
        case 2:
        case 5:
            originPiece = 1;
            break;
        case 1:
        case 4:
        case 6:
            originPiece = 2;
            break;
        case 3:
        default:
            return;
    }
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        xPrime[i] = piece->x[originPiece] - (piece->y[i] - piece->y[originPiece]);
        yPrime[i] = piece->y[originPiece] + (piece->x[i] - piece->x[originPiece]);
        if ((inactivePieces->grid[xPrime[i]][yPrime[i]]) && 
                (inactivePieces->grid[xPrime[i]][yPrime[i]]))
        {
            return;
        }
    }
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        piece->x[i] = xPrime[i];
        piece->y[i] = yPrime[i];
    }
}

void pieceDeactivate(Game *game, Piece *piece, InactivePieces *inactivePieces)
{
    
    int i, j;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        inactivePieces->grid[piece->x[i]][piece->y[i]] = INACTIVE;
        for (j = 0; j < NUM_COLORS; j++)
        {
            inactivePieces->color[piece->x[i]][piece->y[i]][j] = piece->color[j];
        } 
    }
}

int inactivePieceCheck(Game *game, InactivePieces *inactivePieces) 
{
    int x, y;
    for (y = 0; y < GRID_HEIGHT; y++)
    {
        int line = 1;
        for (x = 0; x < GRID_WIDTH; x++)
        {
            line &= inactivePieces->grid[x][y];
        }
        if (line) return y;
    }
    return -1;
}

int inactivePieceClearRow(Game *game, InactivePieces *inactivePieces, int row)
{
    int x, j;
    for (x = 0; x < GRID_WIDTH; x++)
    {
        inactivePieces->grid[x][row] = 0;
        for (j = 0; j < NUM_COLORS; j++)
        {
            inactivePieces->color[x][row][j] = 0;
        }
    }
    return row;
}

int inactivePieceCheckRowEmpty(Game *game, InactivePieces *inactivePieces, int row)
{
    int x;
    for (x = 0; x < GRID_WIDTH; x++)
    {
        if (inactivePieces->grid[x][row] != 0) return 0;
    }
    return 1;
}

void inactivePieceShiftRows(Game *game, InactivePieces *inactivePieces, int initialRow)
{
    int row, x, j;
    for (row = initialRow; inactivePieceCheckRowEmpty(game, inactivePieces, row - 1) != 1; row -= 1)
    {
        if (inactivePieceCheckRowEmpty(game, inactivePieces, row) != 1) break;
        for (x = 0; x < GRID_WIDTH; x++)
        {
            inactivePieces->grid[x][row] = inactivePieces->grid[x][row - 1];
            for (j = 0; j < NUM_COLORS; j++)
            {
                inactivePieces->color[x][row][j] = inactivePieces->color[x][row - 1][j];
            }
        }
        inactivePieceClearRow(game, inactivePieces, row - 1);
    }
}

int inactivePieceClearRows(Game *game, InactivePieces *inactivePieces)
{
    int rowsCleared = 0;
    int row = inactivePieceCheck(game, inactivePieces);
    while (row != -1)
    {
        rowsCleared += 1;
        inactivePieceShiftRows(game, inactivePieces, inactivePieceClearRow(game, inactivePieces, row));
        row = inactivePieceCheck(game, inactivePieces);
    }
    return rowsCleared;
}
