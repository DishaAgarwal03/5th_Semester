#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10202

struct t{
    int n;
    char ch[200];
};

int main()
{
    struct t send;
    struct sockaddr_in cli;
    int n, clilen;
    int sockfd;

    strcpy(send.ch,"----Hello----");
    send.n=45;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    cli.sin_family=AF_INET;
    cli.sin_addr.s_addr=inet_addr("10.0.2.15");
    cli.sin_port=htons(PORTNO);

    clilen=sizeof(cli);
    connect(sockfd, (struct sockaddr*)&cli, clilen);

    write(sockfd, &send, sizeof(send));
    printf("Sent\n");
}
