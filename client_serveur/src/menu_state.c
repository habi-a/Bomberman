/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Menu function file
*/

#include "../inc/app.h"
#include "../inc/menu_state.h"
#include "../inc/state.h"

#include <stdio.h>
#include <stdlib.h>

static SDL_Texture *menu_background(app_t *app)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;

    surface = IMG_Load("./rsc/menu.png");
    if (surface == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return (NULL);
    }
    texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        return (NULL);
    }
    return (texture);

}

static menu_t *menu_create(app_t *app)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (menu == NULL) {
        fprintf(stderr, "Failed to malloc menu");
        return (NULL);
    }
    menu->texture = menu_background(app);
    if (menu->texture == NULL)
        return(NULL);
    return (menu);
}

static void menu_draw(app_t *app, menu_t *menu)
{
    SDL_Rect full_screen = { 0, 0, app->screen_size.x, app->screen_size.y };

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    SDL_RenderCopy(app->renderer, menu->texture, NULL, &full_screen);
    SDL_RenderPresent(app->renderer);
}

static int menu_event(menu_t *menu, int *exit_code) 
{
    SDL_Event e;

    menu = menu;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            *exit_code = STATE_EXIT;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *exit_code = STATE_EXIT;
            case SDLK_UP:
                break;
            case SDLK_DOWN:
                break;
            default:
                break;
            }
        }
    }
    return (*exit_code);
}

static void menu_destroy(menu_t *menu)
{
    if (menu != NULL) {
        if (menu->texture != NULL)
            SDL_DestroyTexture(menu->texture);
        free(menu);
    }
}

int menu_run(app_t *app)
{
    int exit_code = STATE_MENU;
    menu_t *menu = menu_create(app);

    if (menu == NULL)
        return (STATE_EXIT);
    while (exit_code == STATE_MENU) {
        menu_draw(app, menu);
        exit_code = menu_event(menu, &exit_code);
        SDL_Delay(20);
    }
    menu_destroy(menu);
    return (exit_code);
}

