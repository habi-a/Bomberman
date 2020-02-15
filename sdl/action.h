/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      defintion
*/

#ifndef _ACTION_H_
#define _ACTION_H_

#include "game.h"

void action(game_t *);
int is_bomb_active_here(game_t *game, SDL_Point *coord);

#endif /* _ACTION_H_ */
