/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      State defintion file
*/

#ifndef _STATE_H_
#define _STATE_H_

#include "menu_state.h"

#define STATE_MENU 0
#define STATE_SERVER 1
#define STATE_CLIENT 2
#define STATE_EXIT 3
#define STATE_NB 4

typedef int (*state_run_t)(app_t *);

#endif /* _STATE_H_ */
