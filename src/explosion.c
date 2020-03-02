/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Explosion function file
*/

#include "../inc/action.h"
#include "../inc/explosion.h"

static player_t *get_owner_bomb(game_t *game, bomb_t *bomb_to_check)
{
    bomb_t *bomb = NULL;

    for (int i = 0; i < NB_PLAYERS; i++) {
        bomb = game->players[i]->bag->first;
        while (bomb != NULL) {
            if (bomb == bomb_to_check)
                return (game->players[i]);
            bomb = bomb->next;
        }
    }
    return (NULL);
}

static int explose_bomb_top(game_t *game, bomb_t *bomb, int range)
{
    player_t *player = NULL;
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x, bomb->coord.y - (range + 1) };

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        return (1);
    } else if ((player = get_player_alive_here(game, &coord)) != NULL) {
        player->is_alive = 0;
    }
    return (0);
}

static int explose_bomb_bottom(game_t *game, bomb_t *bomb, int range)
{
    player_t *player = NULL;
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x, bomb->coord.y + (range + 1) };

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        return (1);
    } else if ((player = get_player_alive_here(game, &coord)) != NULL) {
        player->is_alive = 0;
    }
    return (0);
}

static int explose_bomb_left(game_t *game, bomb_t *bomb, int range)
{
    player_t *player = NULL;
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x - (range + 1), bomb->coord.y };

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        return (1);
    } else if ((player = get_player_alive_here(game, &coord)) != NULL) {
        player->is_alive = 0;
    }
    return (0);
}

static int explose_bomb_right(game_t *game, bomb_t *bomb, int range)
{
    player_t *player = NULL;
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x + (range + 1), bomb->coord.y };

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        return (1);
    } else if ((player = get_player_alive_here(game, &coord)) != NULL) {
        player->is_alive = 0;
    }
    return (0);
}

void explose_bomb(game_t *game, bomb_t *bomb, int power)
{
    bomb->is_active = 0;
    for (int range = 0; range < power; range++) {
        explose_bomb_top(game, bomb, range);
        explose_bomb_bottom(game, bomb, range);
        explose_bomb_left(game, bomb, range);
        explose_bomb_right(game, bomb, range);
    }
}
