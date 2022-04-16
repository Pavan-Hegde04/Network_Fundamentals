#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100

int main()
{
	int sockfd;//to create socket
	
	struct sockaddr_in serverAddress;//server receive on this address
	
	int n;
	char msg1[MAXSZ];
	char msg2[MAXSZ];
	
	//create socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	//initialize the socket addresses
	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons (PORT);
	
	//client connect to server on port
	connect(sockfd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	//send to server and receive from server
	while(1)
	{
		printf("\n Enter message to send to server: \n");
		fgets(msg1,MAXSZ,stdin);
		if(msg1[0]=='#')
			break;
		
		n=strlen(msg1)+1;
		send(sockfd,msg1,n,0);
		
		n=recv(sockfd,msg2,MAXSZ,0);
		
		printf("Receive message from server :: %s \n",msg2);
	}
	return 0;
}
