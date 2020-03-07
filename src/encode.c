/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman
** File description:
**      Encode function file
*/

#include "../inc/server.h"

#include <stdio.h>
#include <string.h>

static void encode_map(game_t *game, char *payload)
{
    for (int i = 0; i < game->map->nb_block; i++)
        payload[strlen(payload)] = game->map->block[i]->is_destroyed + '0';
}

static void encode_bomb(bag_t *bag, char *payload)
{
    bomb_t *bomb = bag->first;

    for (int i = 0; i < bag->size && bomb != NULL; i++) {
        char tmp_bomb_payload[16] = { 0 };

        sprintf(tmp_bomb_payload, ",%d,%d,%d"
                , bomb->is_active, bomb->coord.x, bomb->coord.y);
        strcat(payload, tmp_bomb_payload);
        bomb = bomb->next;
    }
}

static void encode_player(game_t *game, int index_player, char *payload)
{
    char tmp_payload[16] = { 0 };
    player_t *player_selected = game->players[index_player];

    sprintf(tmp_payload, "%d,%d,%d,%d"
            , player_selected->is_alive
            , player_selected->coord.x, player_selected->coord.y
            , player_selected->bag->size);
    if (payload[0] != 0)
        strncat(payload, tmp_payload, sizeof(payload) - strlen(payload) - 1);
    else
        strncpy(payload, tmp_payload, BUF_SIZE - 1);
    encode_bomb(player_selected->bag, payload);
}

void encode_game(game_t *game, char *payload)
{
    for (int i = 0; i < 4; i++) {
        encode_player(game, i, payload);
        strncat(payload, "\n", sizeof(payload) - strlen(payload) - 1);
    }
    encode_map(game, payload);
}

void encode_first_info(game_t *game, char *payload)
{
    sprintf(payload, "%d %s", game->max_bombs, game->map_selected);
}
