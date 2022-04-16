//UDP Server

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

void toggle(char *,int);

int main()
{
	int sockfd,retval,n,x;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	char buf[1000];
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("sock:");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);
	retval = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval < 0)
	{
		perror("bind:");
		exit(2);
	}
	printf(" socket bound to port 8000\n");
	clilen = sizeof(struct sockaddr_in);
	while(1)
	{
		printf(" before recvfrom\n");
		n=recvfrom(sockfd,buf, 1000,0, (struct sockaddr *)&cliaddr,&clilen);
		buf[n]='\0';
		printf(" message from client = %s\n",buf);
		printf("Toggling message recieved from client\n");
		for(x=0;x<strlen(buf);x++)
		{
			if((buf[x]>='A')&&(buf[x]<='Z'))
			{
				buf[x]+=0x20;
			}
			else if((buf[x]>='a')&&(buf[x]<='z'))
			{
				buf[x]-=0x20;
			}
		}
		sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&servaddr, clilen);
		
	}
	
	
	
	
	return 0;
}

