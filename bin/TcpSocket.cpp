#include "TcpSocket.h"

int initServerTcp(const char* server_ip, unsigned short server_port)
{
    /* sokect */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* bind */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind error");
		close(server_socket);
        exit(-1);
    }

    /* listen */
    if(listen(server_socket, 10) == -1)
    {
        perror("listen error");
		close(server_socket);
        exit(-1);
    }

    return server_socket;
}

int acceptClientTcp(int server_socket)
{
    /* accept */
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr));
    int iLen = sizeof(struct sockaddr);
    int cnnct_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t *)&iLen);
    if(cnnct_socket == -1)
    {
        perror("accept error");
		close(server_socket);
        exit(-1);
    }
    printf("server_ip:%s port:%d has connectd success!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    return cnnct_socket;
}

int connectServerTcp(const char* server_ip, unsigned short server_port)
{
    /* sokect */
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* connect */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect error");
		close(client_socket);
        exit(-1);
    }

    return client_socket;
}
