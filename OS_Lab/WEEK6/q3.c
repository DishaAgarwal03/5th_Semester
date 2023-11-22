#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int isprime(int n)
{
	if (n<2)
		return 0;
	for(int i=2;i<=n/2;i++)
		if (n%i==0)
			return 0;
	return 1;
}

void* thread_code(void* param)
{
	int *arr = (int*) param;
	int start=arr[0];
	int end=arr[1];
	int k=1;

	for(int i=start;i<=end;i++)
	{
		if (isprime(i))
			arr[k++]=i;
	}
	arr[0]=k;
	return (void*)arr;
}

int main(int arg, char* args[])
{
	pthread_t thread;
	int start= atoi(args[1]);
	int end= atoi(args[2]);

	int arr[100];
	arr[0]=start;
	arr[1]=end;

	pthread_create(&thread, 0, &thread_code, (void*)arr);
	pthread_join(thread,0);

	int n=arr[0];
	printf("Prime numbers: ");
	for(int i=1;i<n;i++)
		printf("%i  ",arr[i]);
	printf("\n");
}