/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      defintion
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>

typedef struct player_s {
    SDL_Point coord;
    SDL_Texture *texture;
} player_t;

player_t *player_init(int, int);
void player_destroy(player_t *);

#endif /* _PLAYER_H_ */
