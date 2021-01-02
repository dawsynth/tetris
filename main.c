#include <stdio.h>
#include "core.h"
#include "logic.h"
#include "render.h"

int main(void)
{
    char title[100];
    Game *game = (Game*) calloc(1, sizeof(Game));
    gameInit(game);

    Piece *piece = (Piece*) calloc(1, sizeof(Piece));
    pieceInit(game, piece);

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
                            pieceRotate(piece, game->grid);
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            pieceMove(game, piece, ACCELERATED_DOWN);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            pieceMove(game, piece, LEFT);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            pieceMove(game, piece, RIGHT);
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
        if (pieceMove(game, piece, DOWN) != 0) closeRequested = 1;
        pieceDraw(game, piece);
        gridDraw(game);
        sprintf(title, "TETRIS ------Score: %ld  Level: %d------", game->score, game->level);
        SDL_SetWindowTitle(game->window, title);
        SDL_RenderPresent(game->renderer);
    }

    // Clean up clean up everybody clean up
    gameTerm(game);
    free(piece);
    free(game);
	return 0;
}

