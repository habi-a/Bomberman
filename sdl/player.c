/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      joueur
*/

#include <stdio.h>

#include "player.h"

player_t *player_init(int x, int y)
{
    player_t *player = malloc(sizeof(player));

    if (player == NULL)
        return NULL;
    player->coord.x = x;
    player->coord.y = y;
    player->texture = NULL;
    return (player);
}

void player_destroy(player_t *player)
{
    if (player) {
        if (player->texture)
            SDL_DestroyTexture(player->texture);
        free(player);
    }
}
