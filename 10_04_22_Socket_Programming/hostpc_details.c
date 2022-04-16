// to get details of the hosts

#include<netdb.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>

int main(int argc,char *argv[])
{
	
	char hostname[HOST_NAME_MAX + 1];
	
			//bits/local_lim.h:#define HOST_NAME_MAX 64
			//bits/posix1_lim.h:#define _POSIX_HOST_NAME 255
	
	hostname[HOST_NAME_MAX] = 0;
	
	if (gethostname(hostname, HOST_NAME_MAX) == 0)
		puts(hostname);
	else
		perror("gethostname");
	return 0;
}
