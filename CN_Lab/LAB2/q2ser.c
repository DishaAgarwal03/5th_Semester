//lab2 q2 server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10200

float findres(int ca, int cb, char op)
{
    switch(op)
    {
        case '+': return ca+cb;
        case '-': return ca-cb;
        case '*': return ca*cb;
        case '/': return (float)ca/cb;
        case '%': return ca%cb;
    }
}

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
			int n;
			int arr[2];
            char c;
			recv(new_socket_id, arr, sizeof(arr), 0);
            recv(new_socket_id, &c, sizeof(c), 0);
            if(c=='/' && arr[1]==0)
            {
                printf("Divide by zero error\n");
                continue;
            }
            printf("Evaluating %d %c %d\n",arr[0],c,arr[1]);
			float res=findres(arr[0],arr[1],c);
			send(new_socket_id, &res, sizeof(res), 0);
			
			close(new_socket_id);
			exit(0);
		}
		
		else{
			wait(NULL);
		}
	}
}
