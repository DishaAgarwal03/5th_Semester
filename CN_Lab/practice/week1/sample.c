#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<unistd.h>  //for read and write
#include<arpa/inet.h> //for inet_addr()

#define PORTNO 10200

int main()
{
    int sockfd,newfd;
    struct sockaddr_in seraddr,cliaddr;
    int clilen;
    int n;

    //creating a socket
    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    //naming the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr=inet_addr("10.0.2.15");
    seraddr.sin_port = htons(PORTNO);

    //binding the port to the socket
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

    //creating a connection queue
    listen(sockfd,5);

    while(1)
    {
        char buf[256];
        printf("Server waiting");

        //accept a connection ... different from connect() ...
        clilen=sizeof(clilen);
        newfd=accept(sockfd,(struct sockaddr*)&cliaddr, &clilen);

        //read and write to client on client_sockfd
        n=read(newfd,buf,sizeof(buf));
        printf("\nClient sent: %s\n",buf);
        n=write(newfd,buf,sizeof(buf));

    }
}