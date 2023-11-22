#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
    struct t get;
    struct sockaddr_in ser,cli;
    int n, clilen;
    int sockfd, newfd;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=inet_addr("10.0.2.15");
    ser.sin_port=htons(PORTNO);

    bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));

    listen(sockfd, 5);

    while(1)
    {
        printf("Server waiting\n");

        clilen=sizeof(clilen);
        newfd=accept(sockfd, (struct sockaddr*)&ser, &clilen);

        read(newfd, &get, sizeof(get));
        printf("Client sent %s and %d\n", get.ch, get.n);

    }
}
