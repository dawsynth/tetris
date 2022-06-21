#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "logic.h"
#include "render.h"

char title[100];
GameData *game;

Piece *piece;
Piece *shadowPiece;

GraphicsPackage *graphics;
SDL_Event event;

int closeRequested = 0;

void update_frame() {
    SDL_RenderClear(graphics->renderer);
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
                        pieceRotate(piece, shadowPiece, game->grid);
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        pieceMove(game, piece, shadowPiece, ACCELERATED_DOWN);
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        pieceMove(game, piece, shadowPiece, LEFT);
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        pieceMove(game, piece, shadowPiece, RIGHT);
                        break;
                    case SDL_SCANCODE_SPACE:
                        pieceSlam(game->grid, piece);
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
    if (pieceMove(game, piece, shadowPiece, DOWN) != 0) closeRequested = 1;
    pieceDraw(graphics, piece, 1);
    pieceDraw(graphics, shadowPiece, 0);
    gridDraw(game, graphics);
    sprintf(title, "TETRIS ------Score: %ld  Level: %d------", game->score, game->level);
    SDL_SetWindowTitle(graphics->window, title);
    SDL_RenderPresent(graphics->renderer);
}

int main(void)
{
    game = (GameData*) calloc(1, sizeof(GameData));
    gameInit(game);

    piece = (Piece*) calloc(1, sizeof(Piece));
    shadowPiece = (Piece*) calloc(1, sizeof(Piece));
    pieceInit(game, piece, shadowPiece);

    graphics = (GraphicsPackage*) calloc(1, sizeof(GraphicsPackage));
    graphicsInit(graphics);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(update_frame, 0, 1);
    #else
    while (!closeRequested)
    {
        update_frame();
    }
    #endif

    // Clean up clean up everybody clean up
    gameTerm(game);
    graphicsTerm(graphics);
    free(piece);
    free(game);
	return 0;
}

