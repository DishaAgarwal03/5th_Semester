//lab2 addq2 server without Stop
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10201

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("10.0.2.15");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(sockfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(sockfd, 5);
	
	while(1){

        char buf[256];
        int n=1;
        char words[30][256];
        char w[256];
        char sentence[256];
        int st=0,A=0,B=0,k=0,f=0,count=0;

		struct sockaddr_in cliaddr;
		int clilen = sizeof(cliaddr);  //change?
		int newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
		
		int parent_id = fork();
		
		if(parent_id == 0)
        {

            n = read(newsockfd,buf,sizeof(buf));
            if (strcmp(buf,"Stop")==0)
                continue;
            printf(" \nMessage from client %s \n",buf);
            buf[strlen(buf)]=' ';

            while(buf[st])
            {
                if(buf[st]!=' ')
                    w[B++]=buf[st];
                else
                {
                    
                    w[B]='\0';
                    printf("%s  ",w);
                    for(int m=0;m<A;m++)
                    {
                        if(strcmp(w,words[m])==0)
                        {
                            f=1;
                            count++;
                            break;
                        }
                    }
                    if(f==0)
                        strcpy(words[A++],w);
                    f=0;
                    B=0;
                }
                st++;
            }
            printf("\nNumber of dup words is %d\n",count);
            int ll=0;
            for(int m=0;m<A;m++)
            {
                for(int mk=0;mk<strlen(words[m]);mk++)
                    sentence[ll++]=words[m][mk];
                sentence[ll++]=' ';
            }
            sentence[ll++]='\n';
            sentence[ll]='\0';

            n = write(newsockfd,sentence,sizeof(sentence));
            close(newsockfd);
			// recv(newsockfd, arr, sizeof(arr), 0);
			// send(newsockfd, &res, sizeof(res), 0);
			exit(0);
		}
		
		else{
			wait(NULL);
		}
	}
}
