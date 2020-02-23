/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Server function file
*/

#include "../inc/server.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int client_exists(client_t *clients, sockaddr_in_t *csin, int actual)
{
    int i = 0;

    while (i < actual) {
        if (clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
            && clients[i].sin.sin_port == csin->sin_port)
            return (1);
        i++;
    }
    return (0);
}

client_t *getclient_t(client_t *clients, sockaddr_in_t *csin, int actual)
{
    int i = 0;

    while (i < actual) {
        if (clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
            && clients[i].sin.sin_port == csin->sin_port)
            return (&clients[i]);
        i++;
    }
    return (NULL);
}

void remove_client(client_t *clients, int to_remove, int *actual)
{
    memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove) * sizeof(client_t));
    *actual = *actual - 1;
}

static int init_connection(int port)
{
    int socketfd;
    sockaddr_in_t sin;

    memset(&sin, 0, sizeof(sin));
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        perror("socket()");
        exit(errno);
    }
    printf("\033[0;32m=> Socket has been created.\033[0m\n");
    printf("\033[0;33m=> Attempting to start server...\033[0m\n");
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    if (bind(socketfd, (sockaddr_t *)& sin, sizeof(sin)) == SOCKET_ERROR) {
        perror("bind()");
        exit(errno);
    }
    printf("\033[0;32m=> Server launched and listening on port %d.\033[0m\n", port);
    return (socketfd);
}

void server_launch(app_t *app)
{
    int socketfd = init_connection(app->port);
    int actual_index = 0;
    int max_index = socketfd;
    char buffer[BUF_SIZE];
    fd_set rdfs;
    client_t clients[MAX_CLIENTS];

    while (1) {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(socketfd, &rdfs);
        if (select(max_index + 1, &rdfs, NULL, NULL, NULL) == -1) {
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
                if (client != NULL)
                    send_all_clients(socketfd, clients, client, actual_index, buffer);
            }
            else if (actual_index != MAX_CLIENTS)
            {
                client_t c;

                c.index = actual_index + 1;
                c.sin = csin;
                clients[actual_index] = c;
                actual_index++;
                send_notif_join(socketfd, clients, &c, actual_index);
                printf("Player %d joined the game\n", c.index);
            }
        }
    }
    closesocket(socketfd);
}
