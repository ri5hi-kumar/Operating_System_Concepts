#include<stdio.h>
#include<sys/wait.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 26
#define READ_END 0
#define WRITE_END 1

int main(){
	char input[BUFFER_SIZE];
	char output[BUFFER_SIZE];

	int parent_child[2], child_parent[2];
	pid_t pid;

	if(pipe(parent_child) == -1){
		fprintf(stderr, "Unable to create pipe\n");
		return 1;
	}
	
	if(pipe(child_parent) == -1){
		fprintf(stderr, "Unable to create pipe\n");
		return 1;
	}

	pid = fork();

	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid > 0){
		printf("Enter a string: ");
		fgets(input, BUFFER_SIZE, stdin);
		close(parent_child[READ_END]);
		close(child_parent[WRITE_END]);
		write(parent_child[WRITE_END], input, strlen(input)+1);

		wait(NULL);

		printf("Reversed Case String: ");
		read(child_parent[READ_END], output, strlen(input)+1);
		printf("%s\n", output);
		close(parent_child[WRITE_END]);
		close(child_parent[READ_END]);
	}
	else{
		close(parent_child[WRITE_END]);
		close(child_parent[READ_END]);
		read(parent_child[READ_END], input, BUFFER_SIZE);

		for(int i = 0; i < strlen(input); i++){
			if(input[i] >= 97 && input[i] <= 122){
				output[i] = toupper(input[i]);
			}
			else if(input[i] >= 65 && input[i] <= 90){
				output[i] = tolower(input[i]);
			}
			else{
				output[i] = input[i];
			}
		}
		write(child_parent[WRITE_END], output, strlen(output)+1);
		close(parent_child[READ_END]);
		close(child_parent[WRITE_END]);	
	}

	return 0;
}
