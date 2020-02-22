/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      App defintion file
*/

#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>

typedef struct app_s {
    int tile_size;
    SDL_Point screen_size;
    SDL_Window *window;
    SDL_Renderer *renderer;
} app_t;

app_t *app_start(int, int, int);
void app_destroy(app_t *);

#endif /* _APP_H_ */
