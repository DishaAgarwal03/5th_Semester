#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10201

int main()
{
    struct sockaddr_in cli;
    int n,clilen;
    int sockfd;
    char buf[200];

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    cli.sin_family=AF_INET;
    cli.sin_addr.s_addr=inet_addr("10.0.2.15");
    cli.sin_port=htons(PORTNO);

    clilen=sizeof(cli);
    n=connect(sockfd, (struct sockaddr*)&cli, clilen);

    printf("Enter string: ");
    scanf("%[^\n]s",buf);

    for(int i=0;i<strlen(buf);i++)
        buf[i]+=4;
    printf("Encrypted message: %s\n",buf);

    n=write(sockfd,buf,sizeof(buf));
    n=read(sockfd,buf,sizeof(buf));
    
    printf("Decrypted message: %s\n",buf);
}
