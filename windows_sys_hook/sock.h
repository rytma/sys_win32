#ifndef SOCK_H
#define SOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "error.h"

#define BUFLEN 1024

#define in_addr_t u_long;

#define socket_startup() do { \
        WSADATA data; \
        if (WSAStartup(MAKEWORD(2,2), &data)) { \
            perr_sock("Error: socket startup"); \
            exit(1);
        } \
    } while (0)

#define socket_cleanup() do { \
        if (WSACleanip()) { \
            perr_sock("Error: socket cleanup"); \
            exit(1); \
        } \
    } while (0)

#define is_socket_valid(sock) (sock != INVALID_SOCKET)

#endif