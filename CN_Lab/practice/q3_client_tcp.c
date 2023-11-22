#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.20.10.8");
	address.sin_port = htons(PORTNO);
	
	int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(result == -1){
		printf("\nClient Error");
		exit(-1);
	}
	
	char buffer[256];
	recv(socket_id, buffer, sizeof(buffer), 0);
	printf("\n%s", buffer);
	exit(0);
}
