/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Le fichier principale
*/

#include "check_move.h"

int check_move_up(game_t *game)
{
    if (game->player1->coord.y * game->tile_size - 1 * game->tile_size < 0)
        return (0);
    return (1);
}

int check_move_down(game_t *game)
{
    if (game->player1->coord.y * game->tile_size + 1 * game->tile_size
                            > game->screen_size.y - 1 * game->tile_size)
        return (0);
    return (1);
}

int check_move_left(game_t *game)
{
    if (game->player1->coord.x * game->tile_size - 1 * game->tile_size < 0)
        return (0);
    return (1);
}

int check_move_right(game_t *game)
{
    if (game->player1->coord.x * game->tile_size + 1 * game->tile_size
                            > game->screen_size.x - 1 * game->tile_size)
        return (0);
    return (1);
}
