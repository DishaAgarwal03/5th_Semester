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
    int sd,i,j;
    struct sockaddr_in address;
    sd=socket(AF_INET,SOCK_DGRAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.15");
    address.sin_port=htons(9704);

    int r,c,m,n;
    int mat[30][30];
    printf("Enter number of rows and columns: ");
    scanf("%d %d",&r,&c);
    int len=sizeof(address);
    m=sendto(sd,&r,sizeof(r),0,(struct sockaddr *)&address, len);
    m=sendto(sd,&c,sizeof(c),0,(struct sockaddr *)&address, len);

    for(i=0;i<r;i++)
    {
        int a[30];
        printf("Enter elements of row %d: ",i+1);
        for(j=0;j<c;j++)
            scanf("%d", &a[j]);
        m=sendto(sd,a,sizeof(a),0,(struct sockaddr *)&address, len);
    }

    n=recvfrom(sd,mat,sizeof(mat),0,(struct sockaddr *)&address,&len);
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
            printf("%d  ",mat[i][j]);
        printf("\n");
    }

    
}