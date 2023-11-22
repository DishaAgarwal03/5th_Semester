#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define list_size 5

int list_of_sizes[list_size] = {100,200,102,202,622};

struct mab{
    // int offset;
    int size;
    int allocated;
    struct mab *next;
};

typedef struct mab Mab;
typedef Mab* MabPtr;

MabPtr getnode(int i)
{
    MabPtr Node;
    Node=(MabPtr)malloc(sizeof(Mab));
    Node->next=NULL;
    Node->allocated=-1;
    Node->size=list_of_sizes[i];
    return Node;
}

MabPtr memChk(MabPtr m, int size) // check if memory available , m : head , returns NULL if no block big enough available
{
    while(m)
    {
        if (m->size>=size && m->allocated==-1)
            return m;
        m=m->next;
    }
    printf("Cannot allocate memory to size %d!\n", size);
    return (void*)0;
}

MabPtr memFree(MabPtr m) // free memory block , m : the block to be freed
{
    m->allocated=-1;
}

void FirstFit(MabPtr m, int size) // allocate a memory block , m : head
{
    MabPtr assign = memChk(m,size);
    if(assign == NULL)
        return;
    assign->allocated = size;
}

void BestFit(MabPtr m, int size)
{
    int bestsize = INT_MAX;
    MabPtr assign;
    MabPtr temp = memChk(m,size);  // temp contains first available block
    if(temp == NULL)
        return;
    while(temp)
    {
        if(temp->allocated==-1 && temp->size>=size && temp->size<bestsize)
        {
            assign = temp;
            bestsize = temp->size;
        }
        temp = temp->next;
    }
    assign->allocated=size;
}

void WorstFit(MabPtr m, int size)
{
    int worstsize = INT_MIN;
    MabPtr assign;
    MabPtr temp = memChk(m,size);  // temp contains first available block
    if(temp == NULL)
        return;
    while(temp)
    {
        if(temp->allocated==-1 && temp->size>=size && temp->size>worstsize)
        {
            assign = temp;
            worstsize = temp->size;
        }
        temp = temp->next;
    }
    assign->allocated=size;
}

MabPtr NextFit(MabPtr head, MabPtr m, int size) // allocate a memory block , m : previously assigned block
{
    MabPtr assign = memChk(head,size);
    if(assign == NULL)
        return NULL;
    assign = NULL;
    while(m)
    {
        if(m->allocated==-1 && m->size>=size)
        {
            assign = m;
            break;
        }
        m = m->next;
    }
    if (assign==NULL)
    {
        while(head!=m)
        {
            if(head->allocated==-1 && head->size>=size)
            {
                assign = head;
                break;
            }    
            head = head->next;
        }
    }
    assign->allocated = size;
    return assign; 
}

void display_allocation(MabPtr m)  // m : head
{
    printf("\n");
    while(m)
    {
        printf("Size available: %d \t Allocated: %d\n", m->size, m->allocated);
        m = m->next;
    }
}

void main()
{
    MabPtr head;
    MabPtr temp, cur;
    int allocate_sizes[list_size];
    int i, n, ch;

    // linked list of sizes created
    for(i=0;i<list_size;i++)
    {
        temp = getnode(i);
        if(i==0)
        {
            head = temp;
            cur = head;
        }
        else
        {
            cur->next = temp;
            cur = cur->next;
        }
    }

    printf("Enter the number of processes that need to be allocated: ");
    scanf("%d", &n);
    printf("Enter %d sizes: ", n);
    for(i=0; i<n; i++)
        scanf("%d", &allocate_sizes[i]);
    printf("1. First Fit \n2. Best Fit \n3. Worst Fit \n4. Next Fit \nEnter choice: ");
    scanf("%d", &ch);

    if(ch==1)
    {
        for(int i=0; i<n; i++)
            FirstFit(head,allocate_sizes[i]);
    }
    else if(ch==2)
    {
        for(int i=0; i<n; i++)
            BestFit(head,allocate_sizes[i]);
    }
    else if(ch==3)
    {
        for(int i=0; i<n; i++)
            WorstFit(head,allocate_sizes[i]);
    }
    else if(ch==4)
    {
        MabPtr temp, temp1;
        int c=0;
        for(int i=0; i<n; i++)
        {
            if(c==0)
                temp1 = NextFit(head,head,allocate_sizes[i]);
            else
                temp1 = NextFit(head,temp,allocate_sizes[i]);
            if (temp1!=NULL)
            {
                temp=temp1;
                c=1;
            }
        }     
    }
    else
    {
        printf("Wrong choice!\n");
        exit(0);
    }
    
    display_allocation(head);
}




