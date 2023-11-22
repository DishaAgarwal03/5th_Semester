#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* thread_code(void* param)
{
	int *arr = (int*) param;
	int n=arr[0];
	int sum=0;

	for(int i=1;i<n;i++)
		sum+=arr[i];
	
	return (void*)sum;
}

int main(int arg, char* args[])
{
	pthread_t ethread, othread;
	int esum,osum,n,i;
	int arr[100], earr[100], oarr[100];

	printf("Enter size: ");
	scanf("%d",&n);
	printf("Enter the elements: ");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	int e=1, o=1;
	for(i=0; i<n; i++)
	{
		if(arr[i]%2 == 0)    //even  //arr[i]&1 not working
			earr[e++]=arr[i];
		else
			oarr[o++]=arr[i];
	}
	earr[0]=e;
	oarr[0]=o;

	pthread_create(&ethread, 0, &thread_code, (void*)earr);
	pthread_create(&othread, 0, &thread_code, (void*)oarr);

	pthread_join(ethread,(void**)&esum);
	pthread_join(othread,(void**)&osum);

	printf("Sum of even numbers: %d \nSum of odd numbers: %d \n",esum,osum);
}