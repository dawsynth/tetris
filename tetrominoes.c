#include "tetrominoes.h"

/* 0 - **** 0123
 *           *
 * 1 - *
 *     ***  0123
 *            *
 * 2 -   *  
 *     ***  0123
 *           *
 * 3 - **   No Rotate
 *     **
 *
 * 4 -  *   0123
 *     ***    *
 *
 * 5 -  **  0123
 *     **    *
 *
 * 6 - **   0123
 *      **    *
 */

void tetrominoesInit(SDL_Rect tetrominoes[7][4])
{
    tetrominoes[0][0].w = TILE_WIDTH; tetrominoes[0][0].h = TILE_HEIGHT;
    tetrominoes[0][1].w = TILE_WIDTH; tetrominoes[0][1].h = TILE_HEIGHT;
    tetrominoes[0][2].w = TILE_WIDTH; tetrominoes[0][2].h = TILE_HEIGHT;
    tetrominoes[0][3].w = TILE_WIDTH; tetrominoes[0][3].h = TILE_HEIGHT;

    tetrominoes[1][0].w = TILE_WIDTH; tetrominoes[1][0].h = TILE_HEIGHT;
    tetrominoes[1][1].w = TILE_WIDTH; tetrominoes[1][1].h = TILE_HEIGHT;
    tetrominoes[1][2].w = TILE_WIDTH; tetrominoes[1][2].h = TILE_HEIGHT;
    tetrominoes[1][3].w = TILE_WIDTH; tetrominoes[1][3].h = TILE_HEIGHT;

    tetrominoes[2][0].w = TILE_WIDTH; tetrominoes[2][0].h = TILE_HEIGHT;
    tetrominoes[2][1].w = TILE_WIDTH; tetrominoes[2][1].h = TILE_HEIGHT;
    tetrominoes[2][2].w = TILE_WIDTH; tetrominoes[2][2].h = TILE_HEIGHT;
    tetrominoes[2][3].w = TILE_WIDTH; tetrominoes[2][3].h = TILE_HEIGHT;

    tetrominoes[3][0].w = TILE_WIDTH; tetrominoes[3][0].h = TILE_HEIGHT;
    tetrominoes[3][1].w = TILE_WIDTH; tetrominoes[3][1].h = TILE_HEIGHT;
    tetrominoes[3][2].w = TILE_WIDTH; tetrominoes[3][2].h = TILE_HEIGHT;
    tetrominoes[3][3].w = TILE_WIDTH; tetrominoes[3][3].h = TILE_HEIGHT;

    tetrominoes[4][0].w = TILE_WIDTH; tetrominoes[4][0].h = TILE_HEIGHT;
    tetrominoes[4][1].w = TILE_WIDTH; tetrominoes[4][1].h = TILE_HEIGHT;
    tetrominoes[4][2].w = TILE_WIDTH; tetrominoes[4][2].h = TILE_HEIGHT;
    tetrominoes[4][3].w = TILE_WIDTH; tetrominoes[4][3].h = TILE_HEIGHT;

    tetrominoes[5][0].w = TILE_WIDTH; tetrominoes[5][0].h = TILE_HEIGHT;
    tetrominoes[5][1].w = TILE_WIDTH; tetrominoes[5][1].h = TILE_HEIGHT;
    tetrominoes[5][2].w = TILE_WIDTH; tetrominoes[5][2].h = TILE_HEIGHT;
    tetrominoes[5][3].w = TILE_WIDTH; tetrominoes[5][3].h = TILE_HEIGHT;

    tetrominoes[6][0].w = TILE_WIDTH; tetrominoes[6][0].h = TILE_HEIGHT;
    tetrominoes[6][1].w = TILE_WIDTH; tetrominoes[6][1].h = TILE_HEIGHT;
    tetrominoes[6][2].w = TILE_WIDTH; tetrominoes[6][2].h = TILE_HEIGHT;
    tetrominoes[6][3].w = TILE_WIDTH; tetrominoes[6][3].h = TILE_HEIGHT;

    tetrominoes[0][0].x = 3 * TILE_WIDTH; tetrominoes[0][1].x = 4 * TILE_WIDTH; 
    tetrominoes[0][2].x = 5 * TILE_WIDTH; tetrominoes[0][3].x = 6 * TILE_WIDTH;

    tetrominoes[1][0].x = 3 * TILE_WIDTH; tetrominoes[1][1].x = 3 * TILE_WIDTH; 
    tetrominoes[1][2].x = 4 * TILE_WIDTH; tetrominoes[1][3].x = 5 * TILE_WIDTH;

    tetrominoes[2][0].x = 4 * TILE_WIDTH; tetrominoes[2][1].x = 5 * TILE_WIDTH; 
    tetrominoes[2][2].x = 6 * TILE_WIDTH; tetrominoes[2][3].x = 6 * TILE_WIDTH;

    tetrominoes[3][0].x = 4 * TILE_WIDTH; tetrominoes[3][1].x = 4 * TILE_WIDTH; 
    tetrominoes[3][2].x = 5 * TILE_WIDTH; tetrominoes[3][3].x = 5 * TILE_WIDTH;

    tetrominoes[4][0].x = 4 * TILE_WIDTH; tetrominoes[4][1].x = 5 * TILE_WIDTH; 
    tetrominoes[4][2].x = 5 * TILE_WIDTH; tetrominoes[4][3].x = 6 * TILE_WIDTH;

    tetrominoes[5][0].x = 3 * TILE_WIDTH; tetrominoes[5][1].x = 4 * TILE_WIDTH; 
    tetrominoes[5][2].x = 4 * TILE_WIDTH; tetrominoes[5][3].x = 5 * TILE_WIDTH;

    tetrominoes[6][0].x = 4 * TILE_WIDTH; tetrominoes[6][1].x = 5 * TILE_WIDTH; 
    tetrominoes[6][2].x = 5 * TILE_WIDTH; tetrominoes[6][3].x = 6 * TILE_WIDTH;


    tetrominoes[0][0].y = 1 * TILE_HEIGHT; tetrominoes[0][1].y = 1 * TILE_HEIGHT;
    tetrominoes[0][2].y = 1 * TILE_HEIGHT; tetrominoes[0][3].y = 1 * TILE_HEIGHT;

    tetrominoes[1][0].y = 1 * TILE_HEIGHT; tetrominoes[1][1].y = 2 * TILE_HEIGHT;
    tetrominoes[1][2].y = 2 * TILE_HEIGHT; tetrominoes[1][3].y = 2 * TILE_HEIGHT;

    tetrominoes[2][0].y = 2 * TILE_HEIGHT; tetrominoes[2][1].y = 2 * TILE_HEIGHT;
    tetrominoes[2][2].y = 2 * TILE_HEIGHT; tetrominoes[2][3].y = 1 * TILE_HEIGHT;

    tetrominoes[3][0].y = 1 * TILE_HEIGHT; tetrominoes[3][1].y = 2 * TILE_HEIGHT;
    tetrominoes[3][2].y = 1 * TILE_HEIGHT; tetrominoes[3][3].y = 2 * TILE_HEIGHT;

    tetrominoes[4][0].y = 2 * TILE_HEIGHT; tetrominoes[4][1].y = 1 * TILE_HEIGHT;
    tetrominoes[4][2].y = 2 * TILE_HEIGHT; tetrominoes[4][3].y = 2 * TILE_HEIGHT;

    tetrominoes[5][0].y = 2 * TILE_HEIGHT; tetrominoes[5][1].y = 2 * TILE_HEIGHT;
    tetrominoes[5][2].y = 1 * TILE_HEIGHT; tetrominoes[5][3].y = 1 * TILE_HEIGHT;

    tetrominoes[6][0].y = 1 * TILE_HEIGHT; tetrominoes[6][1].y = 1 * TILE_HEIGHT;
    tetrominoes[6][2].y = 2 * TILE_HEIGHT; tetrominoes[6][3].y = 2 * TILE_HEIGHT;
    return;
}

