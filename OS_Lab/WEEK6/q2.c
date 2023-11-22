#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* thread_code(void* param)
{
	int n = (int) param;
	n = ( n * (n+1) ) / 2;
	return (void*)n;
}

int main(int arg, char* args[])
{
	pthread_t thread;
	int n= atoi(args[1]);
	int rval;

	pthread_create(&thread, 0, &thread_code, (void*)n);
	pthread_join(thread,(void**)&rval);
	printf("Sum: %i\n",rval);
}