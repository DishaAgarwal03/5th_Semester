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
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.0.2.15");
	addr.sin_port = htons(PORTNO);
	
	int result = connect(socket_id, (struct sockaddr*)&addr, sizeof(addr));
	
	if(result == -1){
		printf("\nClient Error");
		exit(-1);
	}
	
	char buffer[256];
	int pid;
	recv(socket_id, &pid, sizeof(pid), 0);  //issue if write this line after buffer line (after recv(buffer))
	recv(socket_id, buffer, sizeof(buffer), 0);
	
	printf("Current time: %s \nProcess id: %d\n", buffer,pid);
	exit(0);
}
