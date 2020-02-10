/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      fichier de jeu
*/

#include <stdio.h>
#include <stdlib.h>

#include "game.h"

game_t *game_init(int screen_width, int screen_heigth)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL) {
        fprintf(stderr, "Failed to malloc game");
        exit(EXIT_FAILURE);
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to initialized the SDL (%s)\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }

    game->screen_size.x = screen_width;
    game->screen_size.y = screen_heigth;
    game->renderer = NULL;
    game->window = NULL;
    return (game);
}

void game_cwindow(game_t *game)
{
    game->window = SDL_CreateWindow("Bomberman"
        , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
        , game->screen_size.x, game->screen_size.y, SDL_WINDOW_SHOWN);

    if (game->window == NULL) {
        fprintf(stderr, "Failed to create the window (%s)\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL) {
        fprintf(stderr, "Failed to create the renderer (%s)\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
}

void game_destroy(game_t *game)
{
    SDL_Quit();
    free(game);
}