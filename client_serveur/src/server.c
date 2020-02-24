/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Server function file
*/

#include "../inc/action.h"
#include "../inc/app.h"
#include "../inc/move.h"
#include "../inc/server.h"
#include "../inc/state.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int server_event_keyboard(app_t *app, game_t *game, SDL_Event *e, int actual_index)
{
    int result = STATE_SERVER_SOCKET;

    switch (e->key.keysym.sym) {
    case SDLK_ESCAPE:
        result = STATE_SERVER;
        break;
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_LEFT:
    case SDLK_RIGHT:
        if (actual_index > 1)
            move(app, game, 0, e->key.keysym.sym);
        break;
    case SDLK_SPACE:
        if (actual_index > 1)
            action(game, 0);
        break;
    default:
        break;
    }
    return (result);
}

static int server_event(app_t *app, game_t *game, int actual_index)
{
    SDL_Event e;
    int result = STATE_SERVER_SOCKET;

    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            result = STATE_EXIT;
        else if (e.type == SDL_KEYDOWN) {
            result = server_event_keyboard(app, game, &e, actual_index);
        }
    }
    return (result);
}

static void server_waiting_draw(app_t *app, button_t *button)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    button_draw(app, button);
    SDL_RenderPresent(app->renderer);
}

static int init_connection(int port, sockaddr_in_t *sin)
{
    int socketfd;

    memset(sin, 0, sizeof(*sin));
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        perror("socket()");
        exit(errno);
    }
    printf("\033[0;32m=> Socket has been created.\033[0m\n");
    printf("\033[0;33m=> Attempting to start server...\033[0m\n");
    sin->sin_addr.s_addr = htonl(INADDR_ANY);
    sin->sin_port = htons(port);
    sin->sin_family = AF_INET;
    if (bind(socketfd, (sockaddr_t *) sin, sizeof(*sin)) == SOCKET_ERROR) {
        perror("bind()");
        exit(errno);
    }
    printf("\033[0;32m=> Server launched and listening on port %d.\033[0m\n", port);
    return (socketfd);
}

int server_run(app_t *app)
{
    sockaddr_in_t sin;
    int state = STATE_SERVER_SOCKET;
    int socketfd = init_connection(app->port, &sin);
    int actual_index = 0;
    int max_index = socketfd;
    char buffer[BUF_SIZE];
    fd_set rdfs;
    game_t *game = game_create(app);
    client_t clients[MAX_CLIENTS];
    SDL_Rect button_pos1 = { 7.5 * app->tile_size, 10 * app->tile_size
                            , 10 * app->tile_size, 1.1 * app->tile_size };
    button_t *wait_text = button_create(app, "En attente de joueurs...", button_pos1);
    struct timeval waitd = { 0, 0 };

    create_client(&actual_index, sin, clients);
    game->players[actual_index - 1]->is_alive = 1;
    while (state == STATE_SERVER_SOCKET) {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(socketfd, &rdfs);
        if (select(max_index + 1, &rdfs, NULL, NULL, &waitd) == -1) {
            perror("select()");
            exit(errno);
        }
        if (FD_ISSET(STDIN_FILENO, &rdfs))
            break;
        else if (FD_ISSET(socketfd, &rdfs))
        {
            sockaddr_in_t csin;

            memset(&csin, 0, sizeof(csin));
            read_client(socketfd, &csin, buffer);
            if (client_exists(clients, &csin, actual_index)) {
                client_t *client = getclient_t(clients, &csin, actual_index);
                if (client != NULL) {
                    printf("%d %s\n", client->index, buffer);
                    send_all_clients(socketfd, clients, client, actual_index, buffer);
                }
            }
            else if (actual_index != MAX_CLIENTS) {
                create_client(&actual_index, csin, clients);
                game->players[actual_index - 1]->is_alive = 1;
                send_notif_join(socketfd, clients, &clients[actual_index - 1], actual_index);
                printf("Player %d joined the game\n", clients[actual_index - 1].index);
            }
        }
        state = server_event(app, game, actual_index);
        if (actual_index > 1)
            game_draw(app, game);
        else
            server_waiting_draw(app, wait_text);
        SDL_Delay(20);
    }
    button_destroy(wait_text);
    closesocket(socketfd);
    game_destroy(game);
    return (state);
}
