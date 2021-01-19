#include "render.h"

void graphicsInit(GraphicsPackage *graphics)
{
    // Attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }
    graphics->window  = SDL_CreateWindow("Tetris",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
	if (!graphics->window)
	{
		printf("Error Creating Window: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

    // Create renderer which sets up graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    graphics->renderer = SDL_CreateRenderer(graphics->window, -1, render_flags);
    if (!graphics->renderer)
    {
        printf("Error Creating Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(graphics->window);
        SDL_Quit();
        return;
    }
    for (int x = 0; x > GRID_WIDTH; x++)
    {
        for (int y = 0; y > GRID_HEIGHT; y++)
        {
            graphics->gridColors[x][y] = BLACK;
        }
    }
}

void graphicsTerm(GraphicsPackage *graphics)
{
    SDL_DestroyRenderer(graphics->renderer);
	SDL_DestroyWindow(graphics->window);
	SDL_Quit();
}

void pieceDraw(GraphicsPackage *graphics, Piece *piece, int fill)
{
    SDL_Rect tetromino[NUM_ACTIVE_TILES];
    for (int i = 0; i < NUM_ACTIVE_TILES; i++)
    {
        tetromino[i] = (SDL_Rect) {.x = piece->x[i] * TILE_WIDTH, .y = piece->y[i] * TILE_HEIGHT, .w = TILE_WIDTH, .h = TILE_HEIGHT};
    }
    switch (piece->pieceNum)
    {
        case 0:
            SDL_SetRenderDrawColor(graphics->renderer, SKYBLUE.r, SKYBLUE.b, SKYBLUE.g, SDL_ALPHA_OPAQUE);
            break;
        case 1:
            SDL_SetRenderDrawColor(graphics->renderer, BLUE.r, BLUE.b, BLUE.g, SDL_ALPHA_OPAQUE);
            break;
        case 2:
            SDL_SetRenderDrawColor(graphics->renderer, ORANGE.r, ORANGE.b, ORANGE.g, SDL_ALPHA_OPAQUE);
            break;
        case 3:
            SDL_SetRenderDrawColor(graphics->renderer, YELLOW.r, YELLOW.b, YELLOW.g, SDL_ALPHA_OPAQUE);
            break;
        case 4:
            SDL_SetRenderDrawColor(graphics->renderer, PURPLE.r, PURPLE.b, PURPLE.g, SDL_ALPHA_OPAQUE);
            break;
        case 5:
            SDL_SetRenderDrawColor(graphics->renderer, GREEN.r, GREEN.b, GREEN.g, SDL_ALPHA_OPAQUE);
            break;
        case 6:
            SDL_SetRenderDrawColor(graphics->renderer, RED.r, RED.b, RED.g, SDL_ALPHA_OPAQUE);
            break;
        default:
            SDL_SetRenderDrawColor(graphics->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            break;
    }
    if (fill) SDL_RenderFillRects(graphics->renderer, tetromino, NUM_ACTIVE_TILES);
    else SDL_RenderDrawRects(graphics->renderer, tetromino, NUM_ACTIVE_TILES);
    SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void gridDraw(GameData *data, GraphicsPackage *graphics)
{
    int x, y;
    SDL_Rect toDraw = {.x = 0, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT};
    for (x = 0; x < GRID_WIDTH; x++)
    {
        for (y = 0; y < GRID_HEIGHT; y++)
        {
            if (data->grid->status[x][y] == INACTIVE) 
            {
                switch (data->grid->type[x][y])
                {
                    case 0:
                        SDL_SetRenderDrawColor(graphics->renderer, SKYBLUE.r, SKYBLUE.b, SKYBLUE.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 1:
                        SDL_SetRenderDrawColor(graphics->renderer, BLUE.r, BLUE.b, BLUE.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 2:
                        SDL_SetRenderDrawColor(graphics->renderer, ORANGE.r, ORANGE.b, ORANGE.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 3:
                        SDL_SetRenderDrawColor(graphics->renderer, YELLOW.r, YELLOW.b, YELLOW.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 4:
                        SDL_SetRenderDrawColor(graphics->renderer, PURPLE.r, PURPLE.b, PURPLE.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 5:
                        SDL_SetRenderDrawColor(graphics->renderer, GREEN.r, GREEN.b, GREEN.g, SDL_ALPHA_OPAQUE);
                        break;
                    case 6:
                        SDL_SetRenderDrawColor(graphics->renderer, RED.r, RED.b, RED.g, SDL_ALPHA_OPAQUE);
                        break;
                    default:
                        SDL_SetRenderDrawColor(graphics->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                        break;
                }
                toDraw.x = x * TILE_WIDTH;
                toDraw.y = y * TILE_HEIGHT;
                SDL_RenderFillRect(graphics->renderer, &toDraw);
                SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            }
        }
    }
}
