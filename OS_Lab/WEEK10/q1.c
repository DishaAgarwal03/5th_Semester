#include<stdio.h>
#include<stdlib.h>
#include "bankers_algo.c"

void main()
{

    update_need();

    // a
    printf("The Need matrix contains for each process, the number of instances of each resource type that can still be requested\n");
    
    // b
    if (check_safe_state())
        printf("The system is in safe state\n");
    else
        printf("The system is not in safe state\n");

    // c
    int req0[m] = {1,0,2};
    if (accept_request(req0, 1))
    {
        printf("The request can be granted immediately\n");
        display();
        reverse_request;
    }
    else
        printf("The request cannot be granted immediately\n");

    // d
    int req1[m] = {3,3,0};
    if (accept_request(req1, 4))
    {
        printf("The request can be granted immediately\n");
        reverse_request;
    }
    else
        printf("The request cannot be granted immediately\n");

    // e
    int req2[m] = {0,2,0};
    if (accept_request(req2, 0))
    {
        printf("The request can be granted immediately\n");
        reverse_request;
    }
    else
        printf("The request cannot be granted immediately\n");
}