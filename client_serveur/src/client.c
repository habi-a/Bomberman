/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Client function file
*/

#include "../inc/client.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int init_connection(const char *address, int port, sockaddr_in_t *sin)
{
    hostent_t *hostinfo;
    int socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socketfd == INVALID_SOCKET) {
        perror("socket()");
        exit(errno);
    }
    printf("\033[0;32m=> Socket client has been created.\033[0m\n");
    printf("\033[0;33m=> Attempting to connect to %s...\033[0m\n", address);
    if ((hostinfo = gethostbyname(address)) == NULL) {
        fprintf(stderr, "\033[0;31mUnknown host %s.\033[0m\n", address);
        exit(EXIT_FAILURE);
    }
    sin->sin_addr = *(in_addr_bis_t *)hostinfo->h_addr;
    sin->sin_port = htons(port);
    sin->sin_family = AF_INET;
    puts("");
    return (socketfd);
}

int read_server(int socketfd, sockaddr_in_t *sin, char *buffer)
{
    int n = 0;
    socklen_t sinsize = sizeof(*sin);

    if ((n = recvfrom(socketfd, buffer, BUF_SIZE - 1, 0, (sockaddr_t *)sin, &sinsize)) < 0) {
        perror("recvfrom()");
        exit(errno);
    }
    buffer[n] = '\0';
    return (n);
}

void write_server(int socketfd, sockaddr_in_t *sin, const char *buffer)
{
    if (sendto(socketfd, buffer, strlen(buffer), 0, (sockaddr_t *)sin, sizeof(*sin)) < 0) {
        perror("sendto()");
        exit(errno);
    }
}

void client_launch(app_t *app)
{
    int n;
    int socketfd;
    char buffer[BUF_SIZE];
    fd_set rdfs;
    sockaddr_in_t sin;

    memset(&sin, 0, sizeof(sin));
    socketfd = init_connection(app->ip, app->port, &sin);
    write_server(socketfd, &sin, " ");
    while (1) {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(socketfd, &rdfs);
        if (select(socketfd + 1, &rdfs, NULL, NULL, NULL) == -1) {
            perror("select()");
            exit(errno);
        }
        if (FD_ISSET(STDIN_FILENO, &rdfs)) {
            fgets(buffer, BUF_SIZE - 1, stdin); {
                char *p;

                p = NULL;
                if ((p = strstr(buffer, "\n")) != NULL)
                    *p = 0;
                else
                    buffer[BUF_SIZE - 1] = 0;
            }
            write_server(socketfd, &sin, buffer);
        }
        else if (FD_ISSET(socketfd, &rdfs)) {
            if ((n = read_server(socketfd, &sin, buffer)) == 0) {
                printf("\033[0;31mServer disconnected !\033[0m\n");
                break;
            }
            puts(buffer);
        }
    }
    closesocket(socketfd);
}
