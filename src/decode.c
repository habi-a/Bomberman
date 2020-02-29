/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Encode function file
*/

#include "../inc/client.h"

#include <stdio.h>
#include <string.h>

static void decode_player(app_t *app, game_t *game, int index_player, char *payload)
{
    int j = 2;
    char tmp_x[4] = { 0 };
    char tmp_y[4] = { 0 };

    printf("payload: %s\n", payload);
    printf("player %i:\n", index_player);
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
    printf("x: %d, y: %d\n", game->players[index_player]->coord.x, game->players[index_player]->coord.y);
}

static void decode_map(game_t *game, char *payload)
{
    for (int i = 0; payload[i] != '\0'; i++)
        game->map->block[i]->is_destroyed = payload[i] - '0';
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
