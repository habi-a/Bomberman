/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Main file
*/

#include "../inc/app.h"
#include "../inc/state.h"

#include <stdlib.h>

int main()
{
    int state = STATE_MENU;
    const int tile_size = 32;
    app_t *app = app_start(25 * tile_size, 21 * tile_size, tile_size);
    state_run_t state_run[STATE_NB] = {
        &menu_run
    };

    while (state != STATE_EXIT)
        state = state_run[state](app);
    app_destroy(app);
    return (EXIT_SUCCESS);
}
