/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      defintion
*/

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct menu_s {
    SDL_Texture *texture;
} menu_t;

int menu_run(app_t *);

#endif /* _MENU_STATE_H_ */
