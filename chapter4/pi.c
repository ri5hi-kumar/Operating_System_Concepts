// This is the third programming exercise in chapter 4
// We are calculating the value of pi using Monte Carlo method
// As the threads are so simple no error checking is done

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>
#include<time.h>
#include<math.h>

int points_inside = 0;
int total_points;

void *calculate_points(void *)
{
	srand(time(0));
	for(int i = 0; i < total_points; i++) {
		double x = 2.0f * ((double)rand()) / RAND_MAX - 1.0f;
		double y = 2.0f * ((double)rand()) / RAND_MAX - 1.0f;
		double dist = sqrt(x*x + y*y);
		if(dist <= 1)
			points_inside++;
	}
}

int main(int argc, char **argv)
{
	if(argc == 1) {
		printf("No number passed in command line\n");
		return 1;
	}

	int n = atoi(argv[1]);
	total_points = n;

	pthread_t t1;

	pthread_create(&t1, NULL, &calculate_points, NULL);

	pthread_join(t1, NULL);

	double pi = 4 * (double)points_inside / total_points;
	printf("The value of pi: %lf\n", pi);

	return 0;
}
