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

void tetrominoesInit(IntVec tetrominoes[7][4])
{
    tetrominoes[0][0].x = 3; tetrominoes[0][1].x = 4; 
    tetrominoes[0][2].x = 5; tetrominoes[0][3].x = 6;

    tetrominoes[1][0].x = 3; tetrominoes[1][1].x = 3;
    tetrominoes[1][2].x = 4; tetrominoes[1][3].x = 5;

    tetrominoes[2][0].x = 4; tetrominoes[2][1].x = 5;
    tetrominoes[2][2].x = 6; tetrominoes[2][3].x = 6;

    tetrominoes[3][0].x = 4; tetrominoes[3][1].x = 4;
    tetrominoes[3][2].x = 5; tetrominoes[3][3].x = 5;

    tetrominoes[4][0].x = 4; tetrominoes[4][1].x = 5;
    tetrominoes[4][2].x = 5; tetrominoes[4][3].x = 6;

    tetrominoes[5][0].x = 3; tetrominoes[5][1].x = 4;
    tetrominoes[5][2].x = 4; tetrominoes[5][3].x = 5;

    tetrominoes[6][0].x = 4; tetrominoes[6][1].x = 5;
    tetrominoes[6][2].x = 5; tetrominoes[6][3].x = 6;


    tetrominoes[0][0].y = 1; tetrominoes[0][1].y = 1;
    tetrominoes[0][2].y = 1; tetrominoes[0][3].y = 1;

    tetrominoes[1][0].y = 1; tetrominoes[1][1].y = 2;
    tetrominoes[1][2].y = 2; tetrominoes[1][3].y = 2;

    tetrominoes[2][0].y = 2; tetrominoes[2][1].y = 2;
    tetrominoes[2][2].y = 2; tetrominoes[2][3].y = 1;

    tetrominoes[3][0].y = 1; tetrominoes[3][1].y = 2;
    tetrominoes[3][2].y = 1; tetrominoes[3][3].y = 2;

    tetrominoes[4][0].y = 2; tetrominoes[4][1].y = 1;
    tetrominoes[4][2].y = 2; tetrominoes[4][3].y = 2;

    tetrominoes[5][0].y = 2; tetrominoes[5][1].y = 2;
    tetrominoes[5][2].y = 1; tetrominoes[5][3].y = 1;

    tetrominoes[6][0].y = 1; tetrominoes[6][1].y = 1;
    tetrominoes[6][2].y = 2; tetrominoes[6][3].y = 2;
}

