#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <string>

#include <sys/stat.h>

#include "TcpSocket.h"
#include "MiniSearchEngineStd.h"
#include "Configuration.h"

using namespace std;

void *pthfunc(void * arg);

int main(int argc, char const *argv[])
{
    //background
    if (fork() != 0)
    {
        exit(0);
    }
    setsid();
    umask(0);

    Configuration conf;

    string ServerIP = conf.getConfig(IPADDRESS);

    string strport = conf.getConfig(SOCKETPORT);
    stringstream strm(strport);
    unsigned short ServerPort;
    strm >> ServerPort;

	int ServerSocket = initServerTcp(ServerIP.c_str(), ServerPort);

    pthread_t pthid = 0;
    while (1)
    {
        int CnnctSocket = acceptClientTcp(ServerSocket);
        pthread_create(&pthid, NULL, pthfunc, (void *)CnnctSocket);

        //important
        //pthread_join(pthid, NULL);
        
        //close(CnnctSocket);
    }
    
    close(ServerSocket);
	return 0;
}

void *pthfunc(void * arg)
{
    int CnnctSocket = (int)arg;

    while (1)
    {
        char buf[512] = {'\0'};
        if(recv(CnnctSocket, buf, sizeof(buf), 0) == -1)
        {
            perror("recv error");
            close(CnnctSocket);
            exit(-1);
        }
        puts(buf);

        string recvstr(buf);
        if (recvstr == "quit()")
        {
            break;
        }

        //send
        if(send(CnnctSocket, "query result is XXXX", 12, 0) == -1)
        {
            perror("send error");
            close(CnnctSocket);
            exit(-1);
        }
    }

    close(CnnctSocket); 
}