/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      joueur
*/

#include <stdio.h>

#include "player.h"

static player_t *player_init(int x, int y, int tile_size)
{
    player_t *player = malloc(sizeof(player));

    if (player == NULL)
        return NULL;
    player->coord.x = x;
    player->coord.y = y;
    player->position_rect.x = player->coord.x * tile_size;
    player->position_rect.y = player->coord.y * tile_size;
    player->position_rect.w = tile_size;
    player->position_rect.h = tile_size;
    player->texture = NULL;
    return (player);
}

player_t *player_load(SDL_Renderer *renderer, int x, int y, 
                        int tile_size, const char *file)
{
    player_t *player = player_init(x, y, tile_size);

    if (player == NULL) {
        fprintf(stderr, "Failed to create player\n");
        return (NULL);
    }
    SDL_Surface *surface = IMG_Load(file);
    if (surface == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        free(player);
        return (NULL);
    }
    player->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (player->texture == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        free(player);
        return (NULL);
    }
    return (player);
}

void player_draw(player_t *player, SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, player->texture, NULL, &(player->position_rect));
}

void player_destroy(player_t *player)
{
    if (player != NULL) {
        if (player->texture != NULL)
            SDL_DestroyTexture(player->texture);
        free(player);
    }
}
