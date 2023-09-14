// This is the first programming exercise in chapter 4
// We calculate various statistical values of numbers on different threads
// As the threads are so simple no error checking is done

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>

#define SIZE 10

int numbers[SIZE];

double average;
int min = INT_MAX, max = -1;

void *find_average(void *)
{
	int sum = 0;

	for(int i = 0; i < SIZE; i++)
		sum += numbers[i];

	average = sum / 7;
}

void *find_min(void *)
{
	for(int i = 0; i < SIZE; i++) {
		if(numbers[i] < min)
			min = numbers[i];
	}
}

void *find_max(void *)
{
	for(int i = 0; i < SIZE; i++) {
		if(numbers[i] > max)
			max = numbers[i];
	}
}

int main(int argc, char **argv)
{
	if(argc == 1 || argc > SIZE+1) {
		printf("No numbers passed in command line or more than 10 numbers are passed\n");
		return 1;
	}

	for(int i = 1; i <= SIZE; i++) {
		int n = atoi(argv[i]);
		numbers[i-1] = n;
	}

	pthread_t t1, t2, t3;

	pthread_create(&t1, NULL, &find_average, NULL);
	pthread_create(&t2, NULL, &find_min, NULL);
	pthread_create(&t3, NULL, &find_max, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	printf("Average = %f\nMin = %d\nMax = %d\n", average, min, max);

	return 0;
}
