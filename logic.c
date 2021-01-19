#include "logic.h"

void gameInit(GameData *data)
{
    data->time = 0;
    data->score = 0;
    data->level = 0;
    data->rowsCleared = 0;
    tetrominoesInit(data->tetrominoes);

    data->grid = (Grid*) calloc(1, sizeof(Grid));
    int x, y;
    for (x = 0; x < GRID_WIDTH; x++)
    {
        for (y = 0; y < GRID_HEIGHT; y++)
        {
            data->grid->status[x][y] = EMPTY;
            data->grid->type[x][y] = 10;
        }
    }
}

void gameTerm(GameData *data)
{
    free(data->grid);
}

void gameDataScoreUpdate(GameData *data, unsigned int moreRowsCleared)
{
    switch (moreRowsCleared)
    {
        case 1:
            data->score += 40 * (data->level + 1);
            break;
        case 2:
            data->score += 100 * (data->level + 1);
            break;
         case 3:
            data->score += 300 * (data->level + 1);
            break;
        case 4:
            data->score += 1200 * (data->level + 1);
            break;
        default:
            break;
    }

    data->rowsCleared += moreRowsCleared;
    if (data->rowsCleared >= 10)
    {
        data->level += 1;
        data->rowsCleared -= 10;
    }
}

int pieceInit(GameData *data, Piece *piece, Piece *shadowPiece)
{
    int i;
    piece->pieceNum = rand() % 7;
    shadowPiece->pieceNum = piece->pieceNum;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        piece->x[i] = data->tetrominoes[piece->pieceNum][i][0];
        piece->y[i] = data->tetrominoes[piece->pieceNum][i][1];
        shadowPiece->x[i] = piece->x[i];
        shadowPiece->y[i] = piece->y[i];
        if (data->grid->status[piece->x[i]][piece->y[i]] == INACTIVE) return -1;
    }
    if (data->time <= 0) piece->pieceMoved = 0;
    pieceSlam(data->grid, shadowPiece);
    return 0;
}

int pieceMove(GameData *data, Piece *piece, Piece *shadowPiece, enum DIRECTION dir)
{
    int i;
    switch(dir)
    {
        case RIGHT:
            if (!(pieceCollide(piece, data->grid, dir))) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    shadowPiece->y[i] = piece->y[i];
                    piece->x[i] += SPEED;
                    shadowPiece->x[i] = piece->x[i];
                }
                pieceSlam(data->grid, shadowPiece);
            }
            break;
        case LEFT:
            if (!(pieceCollide(piece, data->grid, dir))) { 
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    shadowPiece->y[i] = piece->y[i];
                    piece->x[i] -= SPEED;
                    shadowPiece->x[i] = piece->x[i];
                }
                pieceSlam(data->grid, shadowPiece);
            }
            break;
        case ACCELERATED_DOWN:
            if (!(pieceCollide(piece, data->grid, dir))) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->y[i] += SPEED;
                }
                piece->pieceMoved = data->time;
            }
            break;
        case DOWN:
        default:
            if (!(pieceCollide(piece, data->grid, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (data->level * 5))  <= data->time)) {
                for (i = 0; i < NUM_ACTIVE_TILES; i++)
                {
                    piece->y[i] += SPEED;
                }
                piece->pieceMoved = data->time; 
            }
            else if ((pieceCollide(piece, data->grid, dir)) && (piece->pieceMoved + (1000 / 60) * (48 - (data->level * 5)) <= data->time)) {
                pieceDeactivate(piece, data->grid);
                unsigned int rowsCleared = gridClearRows(data->grid);
                gameDataScoreUpdate(data, rowsCleared);
                if (pieceInit(data, piece, shadowPiece) != 0) return -1;
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

void pieceSlam(Grid *grid, Piece *piece)
{
    int i;
    while (!pieceCollide(piece, grid, ACCELERATED_DOWN))
    {
        for (i = 0; i < NUM_ACTIVE_TILES; i++)
        {
            piece->y[i] += SPEED;
        }
    }
}

void pieceRotate(Piece *piece, Piece *shadowPiece, Grid *grid)
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
        shadowPiece->x[i] = piece->x[i];
        piece->y[i] = yPrime[i];
        shadowPiece->y[i] = piece->y[i];
    }
    pieceSlam(grid, shadowPiece);
}

void pieceDeactivate(Piece *piece, Grid *grid)
{
    
    int i;
    for (i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        grid->status[piece->x[i]][piece->y[i]] = INACTIVE;
        grid->type[piece->x[i]][piece->y[i]] = piece->pieceNum;
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

