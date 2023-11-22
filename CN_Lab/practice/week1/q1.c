#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10201

int main()
{
    int sockfd,newfd;
    struct sockaddr_in ser,cli;
    char buf[200];
    int n, clilen;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=inet_addr("10.0.2.15");
    ser.sin_port=htons(PORTNO);

    bind(sockfd,(struct sockaddr*)&ser, sizeof(ser));

    listen(sockfd,5);

    while(1)
    {
        printf("Server waiting\n");
        
        clilen=sizeof(clilen);
        newfd=accept(sockfd,(struct sockaddr*)&cli, &clilen);

        n=read(newfd, buf, sizeof(buf));
        printf("Encrypted message: %s\n",buf);
        for(int i=0;i<strlen(buf);i++)
            buf[i]-=4;
        printf("Decrypted message: %s\n",buf);
        n=write(newfd, buf, sizeof(buf));
    }

}
