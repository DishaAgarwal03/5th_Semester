#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10200

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

int main()
{
    struct sockaddr_in ser,cli;
    int n,clilen,len;
    int sockfd,newfd;
    pid_t pid,p;

    int arr[100];

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=inet_addr("10.0.2.15");
    ser.sin_port=htons(PORTNO);

    bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));

    listen(sockfd,5);

    while(1)
    {
        printf("Server waiting.....\n");
        
        clilen=sizeof(clilen);
        newfd=accept(sockfd,(struct sockaddr*)&cli,&clilen);
        pid=fork();

        if(pid==0)
        {
            //child
            printf("Entered Child\n");
            p=getpid();

            n=recv(newfd,arr,sizeof(arr),0);
            n=recv(newfd,&len,sizeof(len),0);
            printf("Received data\n");
            sortArray(arr,len);
            printf("Sorted data\n");
            n=send(newfd,arr,sizeof(arr),0);
            n=send(newfd,&p,sizeof(p),0);
            close(newfd);
        }
        else
            {
                printf("Entered Parent\n");
                wait(NULL);}
    }
}