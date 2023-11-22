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

void sortArray(int array[], int n);

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("172.16.59.36");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	while(1){
		struct sockaddr_in clientaddress;
		int client = sizeof(clientaddress);
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
		
		int parent_id = fork();
		
		if(parent_id == 0){
			int process_id = getpid();
			int n;
			int array[256];
			recv(new_socket_id, &n, sizeof(n), 0);
			recv(new_socket_id, array, sizeof(array), 0);
			sortArray(array, n);
			send(new_socket_id, array, sizeof(array), 0);
			send(new_socket_id, &process_id, sizeof(process_id), 0);
			
			close(new_socket_id);
			exit(0);
		}
		
		else{
			wait(NULL);
		}
	}
}

void sortArray(int array[], int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(array[j] > array[j + 1]){
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}