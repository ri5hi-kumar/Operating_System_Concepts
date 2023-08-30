#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){
		printf("This is the child process\n");
		int n;
		printf("Enter the integer: \n");
		scanf("%d", &n);
		if(n < 0){
			printf("Enter a positive number\n");
			return 0;
		}

		printf("Conjecture is: %d ", n);
		while(n != 1){
			if(n % 2 == 0){
				n /= 2;
			} else {
				n = 3 * n + 1;
			}
			printf("%d ", n);
		}
		printf("\n");
	}
	else{
		printf("This is the parent process\n");
		wait(NULL);
		return 0;
	}
}
