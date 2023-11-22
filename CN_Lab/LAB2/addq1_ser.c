//lab2 addq1 server
#include <stdio.h>
#include <time.h>  //added
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("10.0.2.15");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	while(1){
		struct sockaddr_in clientaddress;
		int client = sizeof(clientaddress);
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
		
		int parent_id = fork();
		
		if(parent_id == 0){
			int pid=getpid();
			char timevar[50];
			time_t ctime;
			struct tm *time_info;
			time(&ctime);
			time_info = localtime(&ctime);
			strftime(timevar, sizeof(timevar)," %Y-%m-%d %H:%M:%S", time_info);
			send(new_socket_id, &pid, sizeof(pid), 0);
			send(new_socket_id, timevar, sizeof(timevar), 0);
			
			printf("Returning Current time\n");
			close(new_socket_id);
			exit(0);
		}
		
		else{
			wait(NULL);
		}
	}
}
