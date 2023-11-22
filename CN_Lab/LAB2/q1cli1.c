#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	address.sin_addr.s_addr = inet_addr("172.16.59.36");
	address.sin_port = htons(PORTNO);
	
	int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(result == -1){
		perror("\nClient Error");
		exit(0);
	}
	
	int array[256];
	int n;
	int process_id;
	int sorted_array[256];
	printf("\nEnter size of array: ");
	scanf("%d", &n);
	printf("\nEnter array elements: ");
	for(int i = 0; i < n; i++){
		scanf("%d", &array[i]);
	}
	
	send(socket_id, &n, sizeof(n), 0);
	send(socket_id, array, sizeof(array), 0);
	
	recv(socket_id, sorted_array, sizeof(sorted_array), 0);
	recv(socket_id, &process_id, sizeof(process_id), 0);
	
	for(int i = 0; i < n; i++){
		printf("%d ", sorted_array[i]);
	}
	printf("\nProcess ID is : %d", process_id);
	close(socket_id);
}