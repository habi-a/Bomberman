/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      application file
*/

#include "app.h"

static int app_event()
{
    SDL_Event e;
    int result = 1;

    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            result = 0;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                result = 0;
                break;
            default:
                break;
            }
        }
    }
    return (result);
}

void app_run(game_t *game)
{
    int game_is_running = 1;

    while (game_is_running) {
        game_draw(game);
        game_is_running = app_event();
        SDL_Delay(20);
    }
}
