/*socket tcp¿Í»§¶Ë*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERVER_PORT 50001
#define BUF_SIZE 1024
#define SERVER_IP "182.151.116.130"
int main()
{  
	struct sockaddr_in serverAddr;
	char    sendbuf[BUF_SIZE] = {0};
	char    recvbuf[BUF_SIZE] = {0};
	int     iDataNum          = 0;
	int     clientSocket      = 0;
	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket failed\n");
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("connect failed[%d]\n",errno);
		return 1;
	}

	printf("connect with destination host...\n");

	while(1)
	{
		printf("Input your world:>");
		scanf("%s", sendbuf);
		printf("\n");

		send(clientSocket, sendbuf, strlen(sendbuf), 0);
		if(strcmp(sendbuf, "quit") == 0)
			break;
		iDataNum = recv(clientSocket, recvbuf, 200, 0);
		recvbuf[iDataNum] = '\0';
		printf("recv data of my world is:\n %s\n", recvbuf);
	}
	close(clientSocket);
	return 0;
}
