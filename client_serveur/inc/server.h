/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Server defintion file
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "app.h"
#include "game.h"
#include "button.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define  BUF_SIZE            1024
#define  MAX_CLIENTS 	      4
#define  INVALID_SOCKET      -1
#define  SOCKET_ERROR        -1
#define  closesocket(s)      close(s)

typedef   struct sockaddr_in  sockaddr_in_t;
typedef   struct sockaddr     sockaddr_t;
typedef   struct in_addr      in_addr_bis_t;

typedef   struct              s_client {
    sockaddr_in_t             sin;
    int                       index;
}                             client_t;

client_t  create_client(int *actual_index, sockaddr_in_t csin, client_t clients[MAX_CLIENTS]);
int       read_client(int socketfd, sockaddr_in_t *csin, char *buffer);
int       client_exists(client_t *clients, sockaddr_in_t *csin, int actual);
int       server_run(app_t *app);
void      send_notif_join(int socketfd, client_t *clients, client_t *sender, int actual);
void      send_all_clients(int socketfd, client_t *clients, client_t *client, int actual, const char *buffer);
void      remove_client(client_t *clients, int to_remove, int *actual);
client_t *getclient_t(client_t *clients, sockaddr_in_t *csin, int actual);

#endif /* _SERVER_H_ */
