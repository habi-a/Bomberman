/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Le fichier principale
*/

#include <stdlib.h>

#include "game.h"

int main()
{
    game_t *game = game_init(640, 480, 24);

    game_create_window(game);
    game->player1 = player_load(game->renderer, 0, 0, game->tile_size, "./mario.png");
    if (game->player1 == NULL) {
        game_destroy(game);
        return (EXIT_FAILURE);
    }
    game_draw(game);
    SDL_Delay(5000);
    game_destroy(game);
    return (EXIT_SUCCESS);
}
