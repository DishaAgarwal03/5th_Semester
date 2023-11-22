//incomplete
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<error.h>
void main()
{
    int sd;
    char buf[300];
    struct sockaddr_in sadd,cadd;
    sd=socket(AF_INET,SOCK_DGRAM,0);
    if(sd<0)
        perror("Socket error");    

    sadd.sin_family=AF_INET;
    sadd.sin_addr.s_addr=inet_addr("10.0.2.15");
    sadd.sin_port=htons(9704);

    int result=bind(sd,(struct sockaddr*)&sadd, sizeof(sadd));
    if(result<0)
        perror("Binding error");
    int len=sizeof(cadd);
    int m=recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr*)&cadd,&len);
    if(m<0)
    {
        perror("Receive Error\n");
        exit(-1);
    }
    // system(buf); 
    // // in stdlib.h  
    // // gives bad request(sad.htm) 
    execlp("bash","bash","-c",buf,NULL);
    // if execlp did not work only then will the following commands run
    // since exec() replaces the current process with the defined neww process 
    // perror("execlp");   
}