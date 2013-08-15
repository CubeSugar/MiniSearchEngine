#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <string>

#include "TcpSocket.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string ServerIP = "127.0.0.1";
    unsigned short ServerPort = 3546;

	//socket
	int ClientSocket = connectServerTcp(ServerIP.c_str(), ServerPort);

	string QueryWord;

	cout << "enter the query word(\"quit() for exit\"): ";
	while (cin >> QueryWord)
	{
		//send
		if(send(ClientSocket, QueryWord.c_str(), 15, 0) == -1)
		{
			perror("send error");
			close(ClientSocket);
			exit(-1);
		}

    	//recv
		char buf[512] = {'\0'};
		if(recv(ClientSocket, buf, sizeof(buf), 0) == -1)
		{
			perror("recv error");
			close(ClientSocket);
			exit(-1);
		}
		puts(buf);

		if (QueryWord == "quit()")
		{
			break;
		}
		cout << "enter the query word: ";
	}

    //close
	close(ClientSocket);
	return 0;
}