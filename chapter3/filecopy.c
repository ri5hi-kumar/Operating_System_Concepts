#include<stdio.h>
#include<sys/wait.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define BUFFER_SIZE 4096
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
	if(argc != 3) {
		printf("Usage: <command> input.txt copy.txt\n");
		exit(0);
	}

	int input, output;
	int parent_child[2];
	pid_t pid;
	char data[BUFFER_SIZE];
	ssize_t bytes_read, bytes_written;

	input = open(argv[1], O_RDONLY);
	if(input < 0){
		printf("Unable to open the file\n");
		exit(0);
	}
	output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(output < 0){
		printf("Unable to open file\n");
		close(input);
		exit(0);
	}

	if(pipe(parent_child) == -1){
		fprintf(stderr, "Unable to create pipe\n");
		close(input);
		close(output);
		return 1;
	}

	pid = fork();

	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		close(input);
		close(output);
		return 1;
	}
	else if(pid > 0){
		close(parent_child[READ_END]);
		while((bytes_read = read(input, data, BUFFER_SIZE)) > 0){
			bytes_written = write(parent_child[WRITE_END], data,
					bytes_read);
			if(bytes_read != bytes_written){
				close(parent_child[WRITE_END]);
				close(input);
				exit(0);
			}
		}

		close(parent_child[WRITE_END]);
		close(input);
		wait(NULL);
	}
	else{
		close(parent_child[WRITE_END]);
		while((bytes_read = read(parent_child[READ_END], data,
						BUFFER_SIZE)) > 0){
			bytes_written = write(output, data,
					bytes_read);
			if(bytes_read != bytes_written){
				close(parent_child[READ_END]);
				close(output);
				exit(0);
			}
		}

		close(parent_child[READ_END]);
		close(output);
	}

	return 0;
}
