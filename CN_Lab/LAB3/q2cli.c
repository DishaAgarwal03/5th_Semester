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
    address.sin_addr.s_addr=inet_addr("10.0.2.15");
    address.sin_port=htons(9704);

    char requestm[175]= {0};
    char command[300]={0};
    char resourcen[50],hostn[50],outputf[20];
    printf("Enter resource path: ");
    scanf("%s",resourcen);
    printf("Enter host name: ");
    scanf("%s",hostn);
    printf("Enter output file name: ");
    scanf("%s",outputf);
    sprintf(requestm, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", resourcen, hostn);
    sprintf(command,"echo -en '%s'|nc %s 80 > %s",requestm,hostn,outputf);
    //always take care of the sizes of strings you are including
    // if requestm->175 and hostn->50 and 
    // the rest of the characters->30 
    // then command should atleast be 175+50+30

    int len=sizeof(address);
    int m=sendto(sd,command,sizeof(command),0,(struct sockaddr *)&address, len);
    //len in sendto() and &len in recvfrom
    if (m<0)
    {
        perror("Send error\n");
        exit(-1);
    }
}