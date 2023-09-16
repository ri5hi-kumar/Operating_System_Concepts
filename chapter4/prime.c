// This is the second programming exercise in chapter 4
// We are calculating the prime numbers on a different thread
// As the threads are so simple no error checking is done

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>
#include<math.h>

int limit;

int is_prime(int n)
{
	for(int i = 2; i <= sqrt(n); i++) {
		if(n % i == 0)
			return 0;
	}
	return 1;
}

void *print_prime(void *)
{
	for(int i = 2; i <= limit; i++) {
		if(is_prime(i))
			printf("%d ", i);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	if(argc == 1) {
		printf("No number passed in command line\n");
		return 1;
	}

	int n = atoi(argv[1]);
	limit = n;

	pthread_t t1;

	pthread_create(&t1, NULL, &print_prime, NULL);

	pthread_join(t1, NULL);

	return 0;
}
