#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	char buf[200];
	int n;
	char *server_ip="127.0.0.1";
	int sockfd,ret_val;
	struct sockaddr_in server_addr;
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port=htons(8000);	//TCP protocol HTTP----port
	inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
	
	ret_val=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	//printf("client established connection with server \n");
	
	if(ret_val < 0)
	{
		perror("Connect:");
		exit(1);
	}
	printf("client established connection with server \n");
	gets(buf);
	write(sockfd,buf,strlen(buf));
	n=read(sockfd,buf,200);
	buf[n]='\0';
	printf("recived %s from server \n",buf);
	close(sockfd);
	return 0;
}
