/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Encode function file
*/

#include "../inc/server.h"

#include <stdio.h>
#include <string.h>

static void encode_player(game_t *game, int index_player, char *payload)
{
    char tmp_payload[64] = { 0 };
    player_t *player_selected = game->players[index_player];
    bomb_t *bomb = player_selected->bag->first;

    sprintf(tmp_payload, "%d,%d,%d,%d"
            , player_selected->is_alive
            , player_selected->coord.x, player_selected->coord.y
            , player_selected->bag->size);
    while (bomb != NULL) {
        strncat(tmp_payload, ",", sizeof(tmp_payload) - strlen(tmp_payload) - 1);
        tmp_payload[strlen(tmp_payload)] = bomb->is_active + '0';
        bomb = bomb->next;
    }
    if (payload[0] != 0)
        strncat(payload, tmp_payload, sizeof(payload) - strlen(payload) - 1);
    else
        strncpy(payload, tmp_payload, BUF_SIZE - 1);
}

static void encode_map(game_t *game, char *payload)
{
    for (int i = 0; i < game->map->nb_block; i++)
        payload[strlen(payload)] = game->map->block[i]->is_destroyed + '0';
}

void encode_first_info(game_t *game, char *payload)
{
    sprintf(payload, "%d %s", game->max_bombs, game->map_selected);
}

void encode_game(game_t *game, char *payload)
{
    for (int i = 0; i < 4; i++) {
        encode_player(game, i, payload);
        strncat(payload, "\n", sizeof(payload) - strlen(payload) - 1);
    }
    encode_map(game, payload);
}
