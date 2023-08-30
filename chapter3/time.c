#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/time.h>

#define SHARED_MEM_SIZE 128

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Usage: ./time <command>\n");
		return 1;
	}

	pid_t pid;
	struct timeval start_time, end_time;
	void *shared_mem;
	int pipe_fd[2];

	int shared_fd = shm_open("./shared_memory", O_CREAT | O_RDWR, 0666);
	ftruncate(shared_fd, SHARED_MEM_SIZE);
	shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, 
			MAP_SHARED, shared_fd, 0);

	if(pipe(pipe_fd) == -1){
		perror("Pipe creation failed");
		return 1;
	}

	pid = fork();
	if(pid < 0){
		perror("Fork Failed\n");
		return 1;
	} else if(pid == 0){
		gettimeofday(&start_time, NULL);
		memcpy(shared_mem, &start_time, sizeof(struct timeval));
		
		close(pipe_fd[0]);
		write(pipe_fd[1], &start_time, sizeof(struct timeval));
		close(pipe_fd[1]);

		execvp(argv[1], &argv[1]);
	} else{
		wait(NULL);
		
		memcpy(&start_time, shared_mem, sizeof(struct timeval));

		close(pipe_fd[1]);
		write(pipe_fd[0], &start_time, sizeof(struct timeval));
		close(pipe_fd[0]);

		gettimeofday(&end_time, NULL);

		double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
			(end_time.tv_usec - start_time.tv_usec) / 1000000.0;

		printf("Elapsed time: %lf\n", elapsed_time);
	}

	munmap(shared_mem, SHARED_MEM_SIZE);
	close(shared_fd);
	shm_unlink("/shared_memory");

	return 0;
}
