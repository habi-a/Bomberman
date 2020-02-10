/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Game definition
*/

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>


typedef struct game_s {
    SDL_Point       screen_size;
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} game_t;

game_t  *game_init(int, int);
void    game_cwindow(game_t *);
void    game_destroy(game_t *);


#endif /* _GAME_H_ */
