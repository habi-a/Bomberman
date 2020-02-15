/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Le fichier principale
*/

#include "app.h"

#include <stdlib.h>

int main()
{
    const int tile_size = 24;
    game_t *game = game_init(30 * tile_size, 20 * tile_size, tile_size, 2);

    game_create_window(game);
    game->player1 = player_load(game->renderer, 0, 0
                                , game->tile_size, "./mario.png");
    game->player1->bag = bag_load(game->renderer, game->tile_size, 
                                    game->max_bombs, "./apple.png");
    if (game->player1 == NULL || game->player1->bag == NULL) {
        game_destroy(game);
        return (EXIT_FAILURE);
    }
    app_run(game);
    game_destroy(game);
    return (EXIT_SUCCESS);
}
