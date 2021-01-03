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

void tetrominoesInit(unsigned int tetrominoes[7][4][2])
{
    tetrominoes[0][0][0] = 3; tetrominoes[0][1][0] = 4; 
    tetrominoes[0][2][0] = 5; tetrominoes[0][3][0] = 6;

    tetrominoes[1][0][0] = 3; tetrominoes[1][1][0] = 3;
    tetrominoes[1][2][0] = 4; tetrominoes[1][3][0] = 5;

    tetrominoes[2][0][0] = 4; tetrominoes[2][1][0] = 5;
    tetrominoes[2][2][0] = 6; tetrominoes[2][3][0] = 6;

    tetrominoes[3][0][0] = 4; tetrominoes[3][1][0] = 4;
    tetrominoes[3][2][0] = 5; tetrominoes[3][3][0] = 5;

    tetrominoes[4][0][0] = 4; tetrominoes[4][1][0] = 5;
    tetrominoes[4][2][0] = 5; tetrominoes[4][3][0] = 6;

    tetrominoes[5][0][0] = 3; tetrominoes[5][1][0] = 4;
    tetrominoes[5][2][0] = 4; tetrominoes[5][3][0] = 5;

    tetrominoes[6][0][0] = 4; tetrominoes[6][1][0] = 5;
    tetrominoes[6][2][0] = 5; tetrominoes[6][3][0] = 6;


    tetrominoes[0][0][1] = 1; tetrominoes[0][1][1] = 1;
    tetrominoes[0][2][1] = 1; tetrominoes[0][3][1] = 1;

    tetrominoes[1][0][1] = 1; tetrominoes[1][1][1] = 2;
    tetrominoes[1][2][1] = 2; tetrominoes[1][3][1] = 2;

    tetrominoes[2][0][1] = 2; tetrominoes[2][1][1] = 2;
    tetrominoes[2][2][1] = 2; tetrominoes[2][3][1] = 1;

    tetrominoes[3][0][1] = 1; tetrominoes[3][1][1] = 2;
    tetrominoes[3][2][1] = 1; tetrominoes[3][3][1] = 2;

    tetrominoes[4][0][1] = 2; tetrominoes[4][1][1] = 1;
    tetrominoes[4][2][1] = 2; tetrominoes[4][3][1] = 2;

    tetrominoes[5][0][1] = 2; tetrominoes[5][1][1] = 2;
    tetrominoes[5][2][1] = 1; tetrominoes[5][3][1] = 1;

    tetrominoes[6][0][1] = 1; tetrominoes[6][1][1] = 1;
    tetrominoes[6][2][1] = 2; tetrominoes[6][3][1] = 2;
}

