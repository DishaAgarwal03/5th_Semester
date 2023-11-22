#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>	
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define PORTNO 10200

int main(){
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int range = 0;
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("172.20.10.8");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(tcp_socket, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	bind(udp_socket, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	
	listen(tcp_socket, 5);
	
	fd_set readfds;                 // set of file descriptors
	FD_ZERO(&readfds);              // clearing all file descriptorsd
	FD_SET(tcp_socket, &readfds);   // adding the tcp socket to the set
	FD_SET(udp_socket, &readfds);   // adding the udp socket to the set
	
	if(tcp_socket > udp_socket)
		range = tcp_socket;
	else
		range = udp_socket;
	
	while(1){
		fd_set temp_fds = readfds;
		
		int result = select(range + 1, &temp_fds, NULL, NULL, NULL);
		
		if(result == -1){
			printf("\nError Occured");
			exit(-1);
		}
		
		char time_str[50];
		time_t current_time;
		struct tm *time_info;
		time(&current_time);
		time_info = localtime(&current_time);
		strftime(time_str, sizeof(time_str)," %Y-%m-%d %H:%M:%S", time_info);
		
		if(FD_ISSET(udp_socket, &temp_fds)){
			struct sockaddr_in clientaddress;
    			socklen_t client = sizeof(clientaddress);
    			char buffer[256];
			recvfrom(udp_socket, buffer, 256, 0, (struct sockaddr*)&clientaddress, &client);
			sendto(udp_socket, time_str, sizeof(time_str), 0, (struct sockaddr*)&clientaddress, client);
			exit(0);
		}
		
		if(FD_ISSET(tcp_socket, &temp_fds)){
			struct sockaddr_in clientaddress;
			int client = sizeof(clientaddress);
			int new_socket_id = accept(tcp_socket, (struct sockaddr*)&clientaddress, &client);
			send(new_socket_id, time_str, sizeof(time_str), 0);	
		}
	}
	
	close(tcp_socket);
	close(udp_socket);
	return 0;		
}
