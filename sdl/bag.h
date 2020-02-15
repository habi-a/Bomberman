/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      defintion
*/

#ifndef _BAG_H_
#define _BAG_H_

#include <SDL2/SDL.h>

typedef struct bomb_s
{
    int is_active;
    SDL_Point coord;
    SDL_Rect position_rect;
    SDL_Texture *texture;
    struct bomb_s *prev;
    struct bomb_s *next;
} bomb_t;

typedef struct bag_s
{
    int size;
    bomb_t *first;
    bomb_t *last;
} bag_t;

bag_t *bag_load(SDL_Renderer *, int, int, const char *);
void bag_draw(bag_t *, SDL_Renderer *);
void bag_destroy(bag_t *);

bomb_t *bomb_load(SDL_Renderer *, int, const char *);
void bomb_draw(bomb_t *, SDL_Renderer *);
void bomb_destroy(bomb_t *);

#endif /* _BAG_H_ */
