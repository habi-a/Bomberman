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

    game_cwindow(game);
    game_destroy(game);
    return (EXIT_SUCCESS);
}
