//UDP Client

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *serv_ip = "127.0.0.1";
	char msg[100];
	int sockfd,ret_val;
	socklen_t addr_len;
	struct sockaddr_in servaddr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0 )
	{
		perror("error:");
		exit(1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);
	addr_len = sizeof(struct sockaddr_in);
	fgets(msg,20,stdin);
	//send data to the server socket, need not connect to server socket.
	sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&servaddr, addr_len);
	printf(" message from client = %s\n ",msg);
	recvfrom(sockfd,msg, 1000,0, (struct sockaddr *)&servaddr,&addr_len);
	printf(" Toggled message from client = %s\n",msg);
	close(sockfd);
	return 0;
}
