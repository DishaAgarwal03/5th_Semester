#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
    int sd,r,c,len,m,i,j;
    int mat[30][30];
    int a[30];
    struct sockaddr_in sadd,cadd;
    sd=socket(AF_INET,SOCK_DGRAM,0);

    sadd.sin_family=AF_INET;
    sadd.sin_addr.s_addr=inet_addr("172.16.59.15");
    sadd.sin_port=htons(9704);

    int result=bind(sd,(struct sockaddr*)&sadd, sizeof(sadd));
    len=sizeof(cadd);

    m=recvfrom(sd,&r,sizeof(&r),0,(struct sockaddr*)&cadd,&len);
    m=recvfrom(sd,&c,sizeof(&c),0,(struct sockaddr*)&cadd,&len);

    for(i=0;i<r;i++)
    {
        m=recvfrom(sd,a,sizeof(a),0,(struct sockaddr*)&cadd,&len);
        for(j=0;j<c;j++)
            mat[i][j]=a[j];
    }

    printf("Sending matrix\n");
    int n=sendto(sd,mat,sizeof(mat),0,(struct sockaddr*)&cadd,len);   
}