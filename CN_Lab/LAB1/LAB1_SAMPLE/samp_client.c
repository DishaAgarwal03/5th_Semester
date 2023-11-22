#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main()
{
    int len, result,sockfd, n=1;
    struct sockaddr_in address;
    char ch[256], buf[256];

    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    //can give another var name also

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.33");  //ip of server
    address.sin_port=htons(10200);
    //htons for compatibility; if differnet OS, etc.
    len=sizeof(address);

    result=connect(sockfd, (struct sockaddr*)&address,len);
    //not bind, connect; sockfd here is the client socket
    //if no error then result has a non-negative number
    if(result==-1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }

    printf("\nENTER STRING\t");
    gets(ch); 
    //can use scanf() also, then need not append null character since it will be appended by itself 
    //but for gets(), we need to explicitly send. gets(): not a good way
    ch[strlen(ch)]='\0'; 
    //to indicate end of string
    write(sockfd, ch, strlen(ch));
    printf("STRING SENT BACK FROM SERVER IS......");
    while(n)
    {
        n=read(sockfd, buf, sizeof(buf));
        //this is the client buf 
        //use different variables for server and client buf to not get confused
        puts(buf);
    }
}