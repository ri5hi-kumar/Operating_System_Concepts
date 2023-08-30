#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main(){
	const int SIZE = 4096;
	const char *name = "shared";
	int shm_fd;
	int *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){
		ptr = (int *)mmap(0, SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, 
				shm_fd, 0);
		printf("This is the child process\n");
		int n;
		printf("Enter the integer: \n");
		scanf("%d", &n);
		if(n < 0){
			printf("Enter a positive number\n");
			return 0;
		}
		
		int i = 0;
		ptr[i] = n;
		i++;

		while(n != 1){
			if(n % 2 == 0){
				n /= 2;
			} else {
				n = 3 * n + 1;
			}
			ptr[i] = n;
			i++;
		}
		printf("\n");
		munmap(ptr, SIZE);
	}
	else{
		wait(NULL);
		printf("This is the parent process\n");
		ptr = (int *)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		int i = 0;
		while(ptr[i] != 1){
			printf("%d ", ptr[i]);
			i++;
		}
		printf("%d ", ptr[i]);
		printf("\n");
		shm_unlink(name);
		munmap(ptr, SIZE);
	}
	return 0;
}
