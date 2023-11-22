#include<stdio.h>
#include<stdlib.h>

#define m 3  // number of resource types
#define n 5  // number of processes

int allocation[n][m] =
{
    {0,1,0},
    {2,0,0},
    {3,0,2},
    {2,1,1},
    {0,0,2}
};
int max[n][m] = 
{
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}
};
int need[n][m];
int work[m];
int available[m] = {3,3,2};

void update_need()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
}

int compare(int i) // returns 1 if need[i] <= work 
{
    for(int j=0; j<m; j++)
        if( need[i][j] > work[j] )   
            return 0;
    return 1;
}

void display()
{
    int i, j;
    printf("\n\t|Allocation\t|Max\t|Need\t|Available\n");
    for(i=0; i<n; i++)
    {
        printf("P%d      |", i);
        for(j=0; j<m; j++)
            printf("%d ", allocation[i][j]);
        printf("         |");
        for(j=0; j<m; j++)
            printf("%d ", max[i][j]);
        printf(" |");
        for(j=0; j<m; j++)
            printf("%d ", need[i][j]);
        printf(" |");
        if (i==0)
        {    
            for(j=0; j<m; j++)
                printf("%d ", available[j]);
        }
        printf("\n");
    }
    printf("\n");
}

int check_safe_state() // returns 0 if not in safe state else returns 1
{
    int finish[n] = {0};   // 0: False
    int i, j, k;
    int c = 0;
    
    for(j=0; j<m; j++)
        work[j]=available[j];

    while(1)
    {
        k = 0;
        for(i=0; i<n; i++)
        {
            if (finish[i]==0 && compare(i)==1)
            {
                for(j=0;j<m;j++)
                    work[j] += allocation[i][j];
                finish[i] = 1;
                k = 1;
                c++;
            }
            if (c==n)
                return 1;
        }
        if (k == 0)
            return 0;
    }
}

void reverse_request(int req[], int i)
{
    for(int j=0; j<m; j++)
    {
        available[j] += req[j];
        allocation[i][j] -= req[j];
        need[i][j] -= req[j];
    }
}

int accept_request(int req[], int i)   // Process i is requesting resources
{
    for(int j=0; j<m; j++)
    {
        if (available[j]<req[j])
        {
            printf("Requesting more than max");
            return 0;
        }
        available[j] -= req[j];
        allocation[i][j] += req[j];
        need[i][j] -= req[j];
    }
    if (check_safe_state())
    {   
        return 1;
    }
    else
    {
        reverse_request;
        return 0;
    }
}
