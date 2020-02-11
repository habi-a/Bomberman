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
    game_t *game = game_init(640, 480);

    game->player1 = load_player(game, 0, 0, "mario.png");
    game_create_window(game);
    game_destroy(game);
    return (EXIT_SUCCESS);
}
