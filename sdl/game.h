/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Game definition
*/

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>

#include "player.h"

typedef struct game_s {
    // Environment
    int tile_size;
    SDL_Point screen_size;
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Objects
    player_t *player1;

} game_t;

game_t *game_init(int, int, int);
void game_create_window(game_t *);
void game_draw(game_t *);
void game_destroy(game_t *);

#endif /* _GAME_H_ */
