#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct DSA{
    int rid, arrivalts, cylinder;
} DSA;

int n;

void FCFS(DSA dsa[])
{
    int cur=0;
    int tseek = 0;
    for (int i=0;i<n;i++)
    {
        int diff = abs(dsa[i].cylinder - cur);
        printf("Move from %d to %d with seek %d\n",cur,dsa[i].cylinder,diff);
        cur = dsa[i].cylinder;
        tseek+=diff;
    }
    printf("Total seek time : %d\n\n",tseek);
}

void SSTF(DSA dsa[])
{
    int cur = 0;
    int tseek = 0;
    int visited[20]={0};
    while(1)
    {
        int min = INT_MAX;
        int dest = -1;
        for(int i=0;i<n;i++)
        {
            int diff = abs(dsa[i].cylinder - cur);
            if (diff<min && visited[i]==0)
            {
                min = diff;
                dest = i;         
            }
        }
        if (dest==-1)
        {
            printf("Total seek time is %d\n\n",tseek);
            return;
        }
        printf("Move from %d to %d with seek %d\n",cur,dsa[dest].cylinder,min);
        tseek += min;
        cur = dsa[dest].cylinder;
        visited[dest] = 1;
    }
}

void scan(DSA dsa[])
{
    int cur;
    int cyl[n];
    printf("Enter current: ");
    scanf("%d",&cur);
    int tseek = 0;
    for(int i=0;i<n;i++)
    {
        cyl[n]=dsa[i].cylinder;
    }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if (cyl[j]>cyl[j+1])
            {
                int temp = cyl[j];
                cyl[j] = cyl[j+1];
                cyl[j+1] = temp; 
            }
        }
    }
    int i=0;
    while(cur<cyl[i]) i++;
    int k;
    for(;i>=0;i--)
    {
        int diff = cur - cyl[i];
        printf("Move from %d to %d with seek %d",cur, cyl[i], diff);
        cur = cyl[i];
        tseek+=diff;
    }
    tseek+=cur-0;
    cur=0;
    for(int i=)
}

void main()
{
    DSA dsa[]={
        {1, 0, 40},
        {2, 0, 35},
        {3, 0, 10},
        {4, 0, 90},
        {5, 0, 5}
    };
    n = 5;

    // printf("Enter number of read/write(s): ");
    // scanf("%d",&n);
    // printf("Enter rid, arrivalts, cylinder\n");
    // for(int i=0;i<n;i++)
    // {
    //     scanf("%d %d %d", &dsa[i].rid,&dsa[i].arrivalts,&dsa[i].cylinder);
    // }
    
    printf("FFCS:\n");
    FCFS(dsa);
    printf("SSTF:\n");
    SSTF(dsa);
}

