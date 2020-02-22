/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      App function file
*/

#include "../inc/app.h"

#include <stdio.h>
#include <stdlib.h>

static app_t *app_init(int screen_w, int screen_h, int tile_size)
{
    app_t *app = malloc(sizeof(app_t));

    if (app == NULL) {
        fprintf(stderr, "Failed to malloc app");
        exit(EXIT_FAILURE);
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to initialized the SDL: %s\n", SDL_GetError());
        app_destroy(app);
        exit(EXIT_FAILURE);
    }
    app->tile_size = tile_size;
    app->screen_size.x = screen_w;
    app->screen_size.y = screen_h;
    return (app);
}

app_t *app_start(int screen_w, int screen_h, int tile_size)
{
    app_t *app = app_init(screen_w, screen_h, tile_size);

    app->window = SDL_CreateWindow("Bomberman"
        , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
        , app->screen_size.x, app->screen_size.y, SDL_WINDOW_SHOWN);
    if (app->window == NULL) {
        fprintf(stderr, "Failed to create the window: %s\n", SDL_GetError());
        app_destroy(app);
        exit(EXIT_FAILURE);
    }
    app->renderer = SDL_CreateRenderer(app->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL) {
        fprintf(stderr, "Failed to create the renderer: %s\n", SDL_GetError());
        app_destroy(app);
        exit(EXIT_FAILURE);
    }
    return (app);
}


void app_destroy(app_t *app)
{
    if (app != NULL) {
        if (app->renderer != NULL)
            SDL_DestroyRenderer(app->renderer);
        if (app->window != NULL)
            SDL_DestroyWindow(app->window);
        SDL_Quit();
        free(app);
    }
}