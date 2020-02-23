/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\client_server
** File description:
**      Client defintion file
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "app.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define  BUF_SIZE            1024
#define  INVALID_SOCKET      -1
#define  SOCKET_ERROR        -1
#define  closesocket(s)      close(s)

typedef   struct sockaddr_in  sockaddr_in_t;
typedef   struct sockaddr     sockaddr_t;
typedef   struct in_addr      in_addr_bis_t;
typedef   struct hostent      hostent_t;

void      client_launch(app_t *app);
int       read_server(int socketfd, sockaddr_in_t *sin, char *buffer);
void      write_server(int socketfd, sockaddr_in_t *sin, const char *buffer);

#endif /* _CLIENT_H_ */
