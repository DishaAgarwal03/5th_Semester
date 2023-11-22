#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10200

int main()
{
    int sockfd;
    struct sockaddr_in cliaddr;
    int n,result;
    char ch[200],st[200];
    int clilen;

    //create a socket for the client
    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    //name the socket as agreed with the server
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr=inet_addr("10.0.2.15");
    cliaddr.sin_port=htons(PORTNO);

    //connect to server's socket ... different from accept() ...
    clilen=sizeof(cliaddr);
    result=connect(sockfd, (struct sockaddr*)&cliaddr, clilen);

    printf("\nEnter string\n");
    scanf("%[^\n]s",ch);

    n=write(sockfd,ch,sizeof(ch));   //check if strlen or sizeof --> strlen gives issue
    
    n=read(sockfd,st,sizeof(st));
    printf("String sent back from server: %s\n",st);
}

