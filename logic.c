#include "logic.h"

int pieceInit(Game *game, Piece *piece)
{
    int i;
    piece->pieceNum = rand() % 7;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        piece->x[i] = game->tetrominoes[piece->pieceNum][i].x;
        piece->y[i] = game->tetrominoes[piece->pieceNum][i].y;
        if (game->grid->status[piece->x[i]][piece->y[i]] == INACTIVE) return -1;
    }
    if (game->time <= 0) piece->pieceMoved = 0;
    return 0;
}

int pieceMove(Game *game, Piece *piece, enum DIRECTION dir)
{
    int i;
    switch(dir)
    {
        case RIGHT:
            if (!(pieceCollide(piece, game->grid, dir))) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->x[i] += SPEED;
                }
            }
            break;
        case LEFT:
            if (!(pieceCollide(piece, game->grid, dir))) { 
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->x[i] -= SPEED;
                }
            }
            break;
        case ACCELERATED_DOWN:
            if (!(pieceCollide(piece, game->grid, dir))) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->y[i] += SPEED;
                }
                piece->pieceMoved = game->time;
            }
            break;
        case DOWN:
        default:
            if (!(pieceCollide(piece, game->grid, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (game->level * 5))  <= game->time)) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->y[i] += SPEED;
                }
                piece->pieceMoved = game->time; 
            }
            else if ((pieceCollide(piece, game->grid, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (game->level * 5)) <= game->time)) {
                pieceDeactivate(piece, game->grid);
                unsigned int rowsCleared = gridClearRows(game->grid);
                gameScoreUpdate(game, rowsCleared);
                if (pieceInit(game, piece) != 0) return -1;
            }
            break;
    }
    return 0;
}

int pieceCollide(Piece *piece, Grid *grid, enum DIRECTION dir)
{
    int i;
    switch (dir)
    {
        case RIGHT:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->x[i] + 1 >= GRID_WIDTH) return 1;
                else if (grid->status[piece->x[i] + 1][piece->y[i]] == INACTIVE) return 1;
            }
            break;
        case LEFT:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->x[i] == 0) return 1;
                else if (grid->status[piece->x[i] - 1][piece->y[i]] == INACTIVE) return 1;
            }
            break;
        case ACCELERATED_DOWN:
        case DOWN:
        default:
            for (i = 0; i < NUM_ACTIVE_TILES; i++)
            {
                if (piece->y[i] + 1 >= GRID_HEIGHT) return 1;
                else if (grid->status[piece->x[i]][piece->y[i] + 1] == INACTIVE) return 1;
            }
            break;
    }
    return 0;
}

void pieceRotate(Piece *piece, Grid *grid)
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
        if (grid->status[xPrime[i]][yPrime[i]] == INACTIVE) return;
        else if (xPrime[i] >= GRID_WIDTH) return;
        else if (xPrime[i] < 0) return;
    }
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        piece->x[i] = xPrime[i];
        piece->y[i] = yPrime[i];
    }
}

void pieceDeactivate(Piece *piece, Grid *grid)
{
    
    int i;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        grid->status[piece->x[i]][piece->y[i]] = INACTIVE;
    }
}

int gridCheck(Grid *grid) 
{
    int x, y;
    for (y = 0; y < GRID_HEIGHT; y++)
    {
        int line = 1;
        for (x = 0; x < GRID_WIDTH; x++)
        {
            line &= grid->status[x][y];
        }
        if (line) return y;
    }
    return -1;
}

int gridClearRow(Grid *grid, int row)
{
    int x;
    for (x = 0; x < GRID_WIDTH; x++)
    {
        grid->status[x][row] = 0;
    }
    return row;
}

int gridCheckRowEmpty(Grid *grid, int row)
{
    int x;
    for (x = 0; x < GRID_WIDTH; x++)
    {
        if (grid->status[x][row] != 0) return 0;
    }
    return 1;
}

void gridShiftRows(Grid *grid, int initialRow)
{
    int row, x;
    for (row = initialRow; gridCheckRowEmpty(grid, row - 1) != 1; row -= 1)
    {
        if (gridCheckRowEmpty(grid, row) != 1) break;
        for (x = 0; x < GRID_WIDTH; x++)
        {
            grid->status[x][row] = grid->status[x][row - 1];
        }
        gridClearRow(grid, row - 1);
    }
}

int gridClearRows(Grid *grid)
{
    int rowsCleared = 0;
    int row = gridCheck(grid);
    while (row != -1)
    {
        rowsCleared += 1;
        gridShiftRows(grid, gridClearRow(grid, row));
        row = gridCheck(grid);
    }
    return rowsCleared;
}
