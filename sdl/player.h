/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      defintion
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bag.h"

typedef struct player_s {
    bag_t *bag;
    SDL_Point coord;
    SDL_Rect position_rect;
    SDL_Texture *texture;
} player_t;

player_t *player_load(SDL_Renderer *, int, int, int, const char *);
void player_draw(player_t *, SDL_Renderer *);
void player_destroy(player_t *);

#endif /* _PLAYER_H_ */
