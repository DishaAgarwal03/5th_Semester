//incomplete
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
    int sd;
    struct sockaddr_in address;
    sd=socket(AF_INET,SOCK_DGRAM,0);

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.15");
    address.sin_port=htons(9704);

    char requestm[200]= {0};
    char resourcen[100],hostn[100];
    printf("Enter resource path: ");
    scanf("%s",resourcen);
    printf("Enter host name: ");
    scanf("%s",hostn);
    sprintf(requestm, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", resourcen, hostn);

    int len=sizeof(address);
    int m=sendto(sd,requestm,sizeof(requestm),0,(struct sockaddr *)&address, len);

    // int n=recvfrom(sd,requestm,sizeof(requestm),0,(struct sockaddr *)&address,&len);
    // printf("The server echo is %s\n",requestm);
}