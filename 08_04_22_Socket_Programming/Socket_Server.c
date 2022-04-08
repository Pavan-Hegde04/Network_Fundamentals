#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int listfd,connfd,retval;
	//pid_t childpid;
	socklen_t client_len;
	struct sockaddr_in client_addr,server_addr;
	
	listfd=socket(AF_INET, SOCK_STREAM, 0);	//tcp.....connection.../FIFO
	if(listfd < 0)
	{
		perror("Sock:");
		exit(1);
	}
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");	//htonl(INADDR_ANY);
	server_addr.sin_port=htons(8000);	//TCP protocol HTTP----port
	
	retval=bind(listfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(retval < 0)
	{
		perror("Bind:");
		exit(1);
	}
	
	listen(listfd,5);
	while(1)
	{
		client_len=sizeof(client_addr);
		connfd=accept(listfd,(struct sockaddr *)&client_addr,sizeof(client_addr));
		printf("client connected \n");
	}
	
	return 0;
}
