#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* thread_code(void* param)
{
	int *arr = (int*) param;
	int n=arr[0];
	int i=2;
	arr[0]=1;
	if (n==1)
		return (void*)arr;
	arr[1]=1;
	while(i<n)
	{
		arr[i]=arr[i-1]+arr[i-2];
		i++;
	}

	return (void*)arr;
}

int main(int arg, char* args[])
{
	pthread_t thread;
	int n= atoi(args[1]);

	int arr[100];
	arr[0]=n;

	pthread_create(&thread, 0, &thread_code, (void*)arr);
	// pthread_join(thread,(void*)arr);  
	// second parameter gives some error. changes arr[0] and arr[1] to some arbitary value

	// pthread_join(thread,0);
	pthread_join(thread,(void**)arr);
	for(int i=0;i<n;i++)
		printf("%i  ",arr[i]);
	printf("\n");
}