#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORTNO 10200
int main()
{
    int sockfd,newsockfd,portno,clilen,n=1;
    struct sockaddr_in seraddr, cliaddr;  
    //sockaddr_in is a system defined structure in sys/socket.h
    //seraddr, cliaddr are two instances of the type struct sockaddr_in
    int i, value;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);  
    //AF_INET?  for network socket
    //SOCK_STREAM says that it is a TCP connection i.e connection oriented
    //0: protocol number default
    //sockfd is the server socket name here

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.26"); //ip of server
    //struct within struct
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr , sizeof(seraddr));
    //(struct sockaddr*)&seraddr: generic pointer
    //now socket is assigned with ip address, port number and binded to the server

    listen(sockfd,5);
    //now server is ready to receive information from client
    //5: can be changed; max number of clients that can be connected at a time; first come, first serve basis
    //server can reject request also

    while(1)
    {
        char buf[256];
        printf("server waiting");

        clilen=sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        //one more socket is created with accept() (and its address is stored in newsockfd?)
        //client specific socket (newsockfd variable) -> socket for a particular client

        n=read(newsockfd, buf, sizeof(buf));
        //newsockfd is the file descriptor for this read API here and whatever is read is stored in buf
        //buf data type should match with the data type of what the client is sending
        //size: how many bytes of data was sent
        printf("\nMessage from client %s\n",buf);
        n=write(newsockfd, buf, sizeof(buf));
        //sending back data to the client

        //return type of read and write: int -> ACTUAL amount of data read/sent/transferred
    }
}
