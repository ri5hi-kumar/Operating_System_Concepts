// This is the first programming exercise in chapter 4
// We calculate fibonacci sequence on different thread
// As the threads are so simple no error checking is done

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>

#define SIZE 100

int n;
int numbers[SIZE];

void *fibonacci(void *)
{
	int a = 0;
	int b = 1;
	for(int i = 0; i < n; i++) {
		numbers[i] = a;
		int temp = a + b;
		a = b;
		b = temp;
	}
}

int main(int argc, char **argv)
{
	if(argc == 1 || argc > 2) {
		printf("No numbers passed in command line or more than 1 \
			number is passed\n");
		return 1;
	}

	n = atoi(argv[1]);

	if(n > SIZE) {
		printf("Passed number greater than 100\n");
		return 2;
	}

	pthread_t t1;

	pthread_create(&t1, NULL, &fibonacci, NULL);

	pthread_join(t1, NULL);

	printf("Fibonacci sequence is: ");
	for(int i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	return 0;
}
