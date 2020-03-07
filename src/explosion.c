/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman
** File description:
**      Explosion function file
*/

#include "../inc/action.h"
#include "../inc/explosion.h"
#include "../inc/explosion_queue.h"

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

static void explose_bomb_top(app_t *app, game_t *game, bomb_t *bomb, int range
                            , int max)
{
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x, bomb->coord.y - (range + 1) };
    int is_drawable = 1;

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(app, game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        else
            is_drawable = 0;
    }
    if (is_drawable) {
        if (range == max)
            add_explosion(game->explo_queue, &coord, app->tile_size
                        , "./rsc/explosion_top.png", app->renderer);
        else
            add_explosion(game->explo_queue, &coord, app->tile_size
                    , "./rsc/explosion_vert.png", app->renderer);
    }
}

static void explose_bomb_bottom(app_t *app, game_t *game, bomb_t *bomb, int range
                            , int max)
{
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x, bomb->coord.y + (range + 1) };
    int is_drawable = 1;

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(app, game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        else
            is_drawable = 0;
    }
    if (is_drawable) {
        if (range == max)
            add_explosion(game->explo_queue, &coord, app->tile_size
                        , "./rsc/explosion_down.png", app->renderer);
        else
            add_explosion(game->explo_queue, &coord, app->tile_size
                    , "./rsc/explosion_vert.png", app->renderer);
    }
}

static void explose_bomb_left(app_t *app, game_t *game, bomb_t *bomb, int range
                            , int max)
{
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x - (range + 1), bomb->coord.y };
    int is_drawable = 1;

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(app, game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        else
            is_drawable = 0;
    }
    if (is_drawable) {
        if (range == max)
            add_explosion(game->explo_queue, &coord, app->tile_size
                        , "./rsc/explosion_left.png", app->renderer);
        else
            add_explosion(game->explo_queue, &coord, app->tile_size
                    , "./rsc/explosion_hori.png", app->renderer);
    }
}

static void explose_bomb_right(app_t *app, game_t *game, bomb_t *bomb, int range
                            , int max)
{
    bomb_t *bomb_colat = NULL;
    block_t *block = NULL;
    SDL_Point coord = { bomb->coord.x + (range + 1), bomb->coord.y };
    int is_drawable = 1;

    if ((bomb_colat = get_bomb_active_here(game, &coord)) != NULL) {
        explose_bomb(app, game, bomb_colat, get_owner_bomb(game, bomb_colat)->power);
    } else if ((block = get_block_undestroyed_here(game, &coord)) != NULL) {
        if (block->block_type == BLOCK_NORMAL)
            block->is_destroyed = 1;
        else
            is_drawable = 0;
    }
    if (is_drawable) {
        if (range == max)
            add_explosion(game->explo_queue, &coord, app->tile_size
                        , "./rsc/explosion_right.png", app->renderer);
        else
            add_explosion(game->explo_queue, &coord, app->tile_size
                    , "./rsc/explosion_hori.png", app->renderer);
    }
}

static int explose_bomb_center(app_t *app, game_t *game, bomb_t *bomb)
{
    player_t *player = NULL;
    SDL_Point coord = { bomb->coord.x, bomb->coord.y };

    add_explosion(game->explo_queue, &coord, app->tile_size
                    , "./rsc/explosion_center.png", app->renderer);
    if ((player = get_player_alive_here(game, &coord)) != NULL) {
        player->is_alive = 0;
    }
    return (0);
}

void explose_bomb(app_t *app, game_t *game, bomb_t *bomb, int power)
{
    bomb->is_active = 0;
    explose_bomb_center(app, game, bomb);
    for (int range = 0; range < power; range++) {
        explose_bomb_top(app, game, bomb, range, power -1);
        explose_bomb_bottom(app, game, bomb, range, power -1);
        explose_bomb_left(app, game, bomb, range, power -1);
        explose_bomb_right(app, game, bomb, range, power -1);
    }
}
