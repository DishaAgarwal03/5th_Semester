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
	address.sin_addr.s_addr = inet_addr("10.0.2.15");
	address.sin_port = htons(PORTNO);
	
	int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(result == -1){
		perror("\nClient Error");
		exit(0);
	}
	
	float n;
	int arr[2];
    char c;
	float res;

	printf("\nEnter 2 integers and operator: ");
	scanf("%d %d %c", &arr[0], &arr[1], &c);

    send(socket_id, arr, sizeof(arr), 0);
    send(socket_id, &c, sizeof(c), 0);
    if(c=='/' && arr[1]==0)
    {
        printf("Divide by zero error\n");
        exit(0);
    }
	recv(socket_id, &res, sizeof(res), 0);
	
	printf("Result of %d %c %d is %0.3f\n",arr[0],c,arr[1],res);

	close(socket_id);
}