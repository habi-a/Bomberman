/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman
** File description:
**      Game function file
*/

#include "../inc/action.h"
#include "../inc/explosion.h"
#include "../inc/game.h"

#include <stdio.h>
#include <stdlib.h>

static int game_create_players(app_t *app, game_t *game)
{
    game->players[0] = player_load(app->renderer, 1, 1, app->tile_size
                                    , game->max_bombs, "./rsc/player1.png");
    game->players[1] = player_load(app->renderer, 23, 1, app->tile_size
                                    , game->max_bombs, "./rsc/player2.png");
    game->players[2] = player_load(app->renderer, 23, 19, app->tile_size
                                    , game->max_bombs, "./rsc/player3.png");
    game->players[3] = player_load(app->renderer, 1, 19, app->tile_size
                                    , game->max_bombs, "./rsc/player4.png");
    if (game->players[0] == NULL || game->players[1] == NULL
        || game->players[2] == NULL || game->players[3] == NULL)
        return (0);
    return (1);
}

game_t *game_create(app_t *app)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL) {
        fprintf(stderr, "Failed to malloc game\n");
        return (NULL);
    }
    game->explo_queue = create_list_explosion();
    game->max_bombs = app->nb_bomb_start;
    game->map_selected = app->map_selected;
    game->map = map_load(app->renderer, app->tile_size, app->map_selected);
    if (!game_create_players(app, game) || game->map == NULL)
        return (NULL);
    return (game);
}

void game_destroy(game_t *game)
{
    if (game != NULL) {
        for (int i = 0; i < NB_PLAYERS; i++)
            if (game->players[i] != NULL)
                player_destroy(game->players[i]);
        if (game->map != NULL)
            map_destroy(game->map);
        if (game->explo_queue != NULL)
            destroy_list_explosion(game->explo_queue);
        free(game);
    }
}

void game_draw(app_t *app, game_t *game)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    if (game != NULL) {
        map_draw(game->map, app->renderer, app->tile_size);
        for (int i = 0; i < NB_PLAYERS; i++)
            player_draw(game->players[i], app->renderer);
        explosions_draw(game->explo_queue, app->renderer);
    }
}

static int game_update_bomb(app_t *app, game_t *game)
{
    int action_changed = 0;
    bomb_t *bomb = NULL;
    player_t *player = NULL;
    Uint32 time_current = 0;

    for (int i = 0; i < NB_PLAYERS; i++) {
        player = game->players[i];
        for (bomb = player->bag->first; bomb != NULL; bomb = bomb->next) {
            time_current = SDL_GetTicks();
            if (time_current > 3000 + bomb->time_activated && bomb->is_active) {
                explose_bomb(app, game, bomb, player->power);
                action_changed = 1;
            }
        }
    }
    return (action_changed);
}

static int game_update_explosion(game_t *game)
{
    int action_changed = 1;
    Uint32 time_current =  SDL_GetTicks();

    for (explosion_t *temp = game->explo_queue->front; action_changed
            && temp != NULL; temp = game->explo_queue->front) {
        if (time_current > 1000 + temp->time_explosed)
            stop_explosion(game->explo_queue);
        else
            action_changed = 0;
    }
    return (action_changed);
}


int game_update(app_t *app, game_t *game)
{
    int action_changed = 0;

    if (game_update_bomb(app, game))
        action_changed = 1;
    if (game_update_explosion(game))
        action_changed = 1;
    return (action_changed);
}
