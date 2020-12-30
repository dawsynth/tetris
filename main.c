#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "render.h"
#include "tetris.h"
#include "tetrominoes.h"


int main(void)
{
    char title[100];
    Game *game = (Game*) calloc(1, sizeof(Game));
    gameInit(game);
    
    Piece *piece = (Piece*) calloc(1, sizeof(Piece));
    pieceInit(game, piece);
   
    InactivePieces *inactivePieces = (InactivePieces*) calloc(1, sizeof(InactivePieces));
    int x, y;
    for (x = 0; x <= 10; x++)
    {
        for (y = 0; y <= 20; y++)
        {
            inactivePieces->grid[x][y] = 0;
        }
    }
    
    SDL_Event event;

    int closeRequested = 0;

    while (!closeRequested)
    {
        SDL_RenderClear(game->renderer);
        // Process all the events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    closeRequested = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            pieceRotate(game, piece, inactivePieces);
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            pieceMove(game, piece, inactivePieces, ACCELERATED_DOWN);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            pieceMove(game, piece, inactivePieces, LEFT);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            pieceMove(game, piece, inactivePieces, RIGHT);
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            closeRequested = 1;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                        default:
                            break;
                    }            
                    break;
            }
        }
        // Draw Image to Window
        game->time = SDL_GetTicks();
        pieceMove(game, piece, inactivePieces, DOWN);
        pieceDraw(game, piece);
        inactivePieceDraw(game, inactivePieces);
        sprintf(title, "TETRIS ------Score: %ld  Level: %d------", game->score, game->level);
        SDL_SetWindowTitle(game->window, title);
        SDL_RenderPresent(game->renderer);
    }

    // Clean up clean up everybody clean up
    gameTerm(game);
    free(inactivePieces);
    free(piece);
    free(game);
	return 0;
}

