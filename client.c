#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void main() {
	// create client socket
	int clientSocket;
	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

	// define server address
	struct sockaddr_in serverAddr;
	bzero(&serverAddr,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9007);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	int len = sizeof(serverAddr);

	char serverMsg[256];
	char clientMsg[256];
	
        while(1) {
		bzero(&serverMsg, strlen(serverMsg));
                printf("Client > ");
                gets(clientMsg);
                sendto(clientSocket, clientMsg, sizeof(clientMsg), 0, (struct sockaddr*)&serverAddr, len);
		// if message == exit, close socket and exit
		if(strcmp(clientMsg,"exit") == 0) break;
                recvfrom(clientSocket, serverMsg, sizeof(serverMsg), 0, (struct sockaddr*)&serverAddr, &len);
                printf("\nServer : %s\n",serverMsg);
                if(strcmp(serverMsg,"exit") == 0) break;
        }
	close(clientSocket);
}
