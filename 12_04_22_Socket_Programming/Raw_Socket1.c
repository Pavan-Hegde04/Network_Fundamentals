#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<net/ethernet.h>
#include<netpacket/packet.h>

int main()
{
	int pack_socket,n;
	struct sockaddr_ll sa;
	socklen_t sl;
	char buf[2000];
	
	//pack_socket = socket(PF_PACKET, SOCK_RAW,htons(ETH_P_ALL));
	pack_socket = socket(PF_PACKET, SOCK_DGRAM,htons(ETH_P_ALL));
	if(pack_socket < 0)
	{
		printf(" Failed to open packet socket\n");
		exit(0);
	}
	printf(" Packet Socket successfully opened\n");
	while(1)
	{
		sl = sizeof(struct sockaddr_ll);
		n = recvfrom(pack_socket, buf, 2000,0,(struct sockaddr *)&sa,&sl);
		printf(" Received packet of length %d\n", n);
		printf(" Packet Type = %d\n", sa.sll_pkttype);
		printf(" hardware address length %d\n", sa.sll_halen);
		printf(" Protocol %d\n", ntohs(sa.sll_protocol));
	}
	close(pack_socket);
	return 0;
}
