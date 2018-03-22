#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void main() {
	// Message buffers
	char serverMsg[256];
	char clientMsg[256];
	
	// Create server socket
	int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	
	// Define server address and port
	struct sockaddr_in serverAddr;
	bzero(&serverAddr,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9007);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	struct sockaddr_in clientAddr;
	int len = sizeof(clientAddr);
	
	// Bind to port
	int bindStatus = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(bindStatus == -1) {
		printf("Failed to bind to port!\n");
		exit(1);
	}
	printf("Server binded to port 9007\n");
	
	while(1) {
		bzero(&clientMsg, strlen(clientMsg));
                recvfrom(serverSocket, clientMsg, sizeof(clientMsg), 0, (struct sockaddr*)&clientAddr, &len);
                printf("\nClient : %s\n",clientMsg);
		// if message == exit, close socket and exit
		if(strcmp(clientMsg,"exit") == 0) break;
	        printf("Server > ");
                gets(serverMsg);
                sendto(serverSocket, serverMsg, sizeof(serverMsg), 0, (struct sockaddr*)&clientAddr, len);
                // if message == exit, close socket and exit
                if(strcmp(serverMsg,"exit") == 0) break;
         }
	 close(serverSocket);
}
