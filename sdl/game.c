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
        fprintf(stderr, "Failed to initialized the SDL: %s\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }

    game->screen_size.x = screen_width;
    game->screen_size.y = screen_heigth;
    game->renderer = NULL;
    game->window = NULL;
    return (game);
}

void game_create_window(game_t *game)
{
    game->window = SDL_CreateWindow("Bomberman"
        , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
        , game->screen_size.x, game->screen_size.y, SDL_WINDOW_SHOWN);

    if (game->window == NULL) {
        fprintf(stderr, "Failed to create the window: %s\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, 
                                        SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL) {
        fprintf(stderr, "Failed to create the renderer: %s\n", SDL_GetError());
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
}

void game_destroy(game_t *game)
{
    if (game->player1 != NULL)
        player_destroy(game->player1);
    if (game != NULL) {
        if (game->renderer != NULL)
            SDL_DestroyRenderer(game->renderer);
        if (game->window != NULL)
            SDL_DestroyWindow(game->window);
    }
    SDL_Quit();
    free(game);
}

player_t *load_player(game_t *game, int x, int y, const char *file)
{
    player_t *player = player_init(x, y);

    if (player == NULL) {
        fprintf(stderr, "Failed to create player\n");
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
    SDL_Surface *surface = IMG_Load(file);
    if (surface == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        free(player);
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
    player->texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (player->texture == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        free(player);
        game_destroy(game);
        exit(EXIT_FAILURE);
    }
    return (player);
}
