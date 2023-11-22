#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10200

int main()
{
    struct sockaddr_in cli;
    int n, a[100], len, clilen;
    int sockfd;
    pid_t pid;
    int i;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);

    cli.sin_family=AF_INET;
    cli.sin_addr.s_addr=inet_addr("10.0.2.15");
    cli.sin_port=htons(PORTNO);

    clilen=sizeof(cli);
    connect(sockfd,(struct sockaddr*)&cli,clilen);

    printf("Enter size:");
    scanf("%d",&len);
    printf("Enter elements:");
    for(i=0;i<len;i++)
        scanf("%d",&a[i]);

    printf("Unsorted: ");
    for(i=0;i<len;i++)
        printf("%d  ",a[i]);
    printf("\n");

    n=send(sockfd,a,sizeof(a),0);
    n=send(sockfd,&len,sizeof(len),0);

    n=recv(sockfd,a,sizeof(a),0);
    n=recv(sockfd,&pid,sizeof(pid),0);

    printf("Sorted: ");
    for(i=0;i<len;i++)
        printf("%d  ",a[i]);
    printf("\nPID: %d\n",pid);
    close(sockfd);
}
