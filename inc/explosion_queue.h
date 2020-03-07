/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman
** File description:
**      Explosion queue defintion file
*/

#ifndef _EXPLOSION_QUEUE_H_
#define _EXPLOSION_QUEUE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct explosion_s {
    Uint32 time_explosed;
    SDL_Point coord;
    SDL_Rect position_rect;
    SDL_Texture *texture;
    struct explosion_s *next;
} explosion_t;

typedef struct explosion_list_s {
    int size;
    explosion_t *front;
    explosion_t *rear;
} explosion_list_t;

explosion_list_t *create_list_explosion();
void add_explosion(explosion_list_t *, SDL_Point *, int, const char *
                                                    , SDL_Renderer *);
void stop_explosion(explosion_list_t *);
void destroy_list_explosion(explosion_list_t *);

void explosions_draw(explosion_list_t *q, SDL_Renderer *renderer);

#endif /* _EXPLOSION_QUEUE_H_ */
