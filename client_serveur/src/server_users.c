/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Server clients function file
*/

#include "../inc/server.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

client_t create_client(int *actual_index, sockaddr_in_t csin, client_t clients[MAX_CLIENTS])
{
    client_t client;

    client.index = *actual_index + 1;
    client.sin = csin;
    clients[*actual_index] = client;
    *actual_index += 1;
    return (client);
}

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
