#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>

int initServerTcp(const char* server_ip, unsigned short server_port);
int acceptClientTcp(int server_socket);
int connectServerTcp(const char* server_ip, unsigned short server_port);

#endif