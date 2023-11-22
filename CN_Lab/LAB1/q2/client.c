//clientq2
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{

    while(1){
        char buf[256];
    	int n=1;
        int len,result,sockfd;
        struct sockaddr_in address;
        
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family=AF_INET;
        address.sin_addr.s_addr=inet_addr("172.16.59.27"); 
        address.sin_port=htons(10201);
        len = sizeof(address);
        result=connect(sockfd,(struct sockaddr *)&address,len);

        if(result==-1)
        {
            perror("\nCLIENT ERROR");
            exit(1);
        }
        
        char ch[256];
        printf("\nENTER STRING\t");    
        scanf("%[^\n]s",ch);
        getchar();
        ch[strlen(ch)]='\0';
        
        if(strcmp(ch,"Stop")==0)
            exit(0); 
        write(sockfd,ch,sizeof(ch));
        printf("STRING SENT BACK FROM SERVER IS ..... ");
        n=read(sockfd,buf,sizeof(buf));
        printf("%s",buf);
        close(sockfd);
    }
}
