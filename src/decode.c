/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman
** File description:
**      Decode function file
*/

#include "../inc/client.h"

#include <stdio.h>
#include <string.h>

static void decode_map(game_t *game, char *payload)
{
    for (int i = 0; payload[i] != '\0'; i++)
        game->map->block[i]->is_destroyed = payload[i] - '0';
}

static void decode_bomb(app_t *app, bomb_t *bomb, char *payload, int *j)
{
    char tmp_x[4] = { 0 };
    char tmp_y[4] = { 0 };

    bomb->is_active = payload[*j] - '0';
    *j += 2;
    for (int k = 0; payload[*j] != ','; k++) {
        tmp_x[k] = payload[*j];
        *j += 1;
    }
    *j += 1;
    bomb->coord.x = atoi(tmp_x);
    for (int k = 0; payload[*j] != ',' && payload[*j] != 0; k++) {
        tmp_y[k] = payload[*j];
        *j += 1;
    }
    *j += 1;
    bomb->coord.y = atoi(tmp_y);
    bomb_update_pos(bomb, app->tile_size);
}

static void decode_bag(app_t *app, game_t *game, int indexplayer, char *payload
                        , int *j)
{
    int nb_bombs = 0;
    char nb_bombs_str[4] = { 0 };
    bomb_t *bomb = NULL;

    for (int k = 0; payload[*j] != ','; k++) {
        nb_bombs_str[k] = payload[*j];
        *j += 1;
    }
    *j += 1;
    nb_bombs = atoi(nb_bombs_str);
    for (int i = game->players[indexplayer]->bag->size; i < nb_bombs; i++) {
        if (!bag_add(game->players[indexplayer]->bag, app->renderer
            , app->tile_size, "./rsc/bomb.png"))
            return;
    }
    bomb = game->players[indexplayer]->bag->first;
    for (int i = 0; bomb != NULL; i++) {
        decode_bomb(app, bomb, payload, j);
        bomb = bomb->next;
    }
}

static void decode_player(app_t *app, game_t *game, int index_player
                            , char *payload)
{
    int j = 2;
    char tmp_x[4] = { 0 };
    char tmp_y[4] = { 0 };

    game->players[index_player]->is_alive = payload[0] - '0';
    for (int k = 0; payload[j] != ','; k++) {
        tmp_x[k] = payload[j];
        j++;
    }
    j++;
    game->players[index_player]->coord.x = atoi(tmp_x);
    for (int k = 0; payload[j] != ','; k++) {
        tmp_y[k] = payload[j];
        j++;
    }
    j++;
    game->players[index_player]->coord.y = atoi(tmp_y);
    player_update_pos(game->players[index_player], app->tile_size);
    decode_bag(app, game, index_player, payload, &j);
}

void decode_game(app_t *app, game_t *game, char *payload)
{
    int j = 0;
    for (int i = 0; i < 4; i++) {
        char tmp_payload[64] = { 0 };

        for (int k = 0; payload[j] != '\n'; k++) {
            tmp_payload[k] = payload[j];
            j++;
        }
        decode_player(app, game, i, tmp_payload);
        j++;
    }
    decode_map(game, payload + j);
}

void decode_notif(app_t *app, char *payload)
{
    int j = 0;
    char tmp_bombs[4] = { 0 };

    for (int k = 0; payload[j] != ' '; k++) {
        tmp_bombs[k] = payload[j];
        j++;
    }
    app->nb_bomb_start = atoi(tmp_bombs);
    j++;
    app->map_selected = payload + j;
    j++;
}
