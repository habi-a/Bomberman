/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Server i/o function file
*/

#include "../inc/server.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_client(int socketfd, sockaddr_in_t *csin, char *buffer)
{
    int n = 0;
    socklen_t sinsize = sizeof(*csin);

    if ((n = recvfrom(socketfd, buffer, BUF_SIZE - 1, 0, (sockaddr_t *)csin, &sinsize)) < 0) {
        perror("recvfrom()");
        exit(errno);
    }
    buffer[n] = '\0';
    return n;
}

static void write_client(int socketfd, sockaddr_in_t *sin, const char *buffer)
{
    if (sendto(socketfd, buffer, strlen(buffer), 0, (sockaddr_t *)sin, sizeof(*sin)) < 0) {
        perror("sendto()");
        exit(errno);
    }
}

void send_notif_join(int socketfd, client_t *clients, client_t *sender, int actual)
{
    int i = 0;
    char index_player[2];
    char message[BUF_SIZE] = { 0 };

    sprintf(index_player, "%d", sender->index);
    while (i < actual) {
        strncpy(message, "\033[0;32m*** Player ", BUF_SIZE - 1);
        strncat(message, index_player, sizeof(message) - strlen(message) - 1);
        strncat(message, " joined the game ***\033[0m", sizeof(message) - strlen(message) - 1);
        write_client(socketfd, &clients[i].sin, message);
        i++;
    }
}


void send_all_clients(int socketfd, client_t *clients, client_t *sender, int actual, const char *buffer)
{
    int i = 0;

    while (i < actual) {
        if (sender != &clients[i])
            write_client(socketfd, &clients[i].sin, buffer);
        i++;
    }
}
