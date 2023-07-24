#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_LINE 80
#define BUFFER_SIZE 1024

char *sh_read_command(void)
{
	int size = BUFFER_SIZE;
	char *buffer = malloc(sizeof(char) * size);
	int position = 0;
	int ch;

	if (!buffer) {
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		ch = getchar();

		if (ch == EOF || ch == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = ch;
		}
		position++;
	}

	if (position >= size) {
		size += BUFFER_SIZE;
		buffer = realloc(buffer, size);
		if (!buffer) {
			fprintf(stderr, "sh: allocation error\n");
			exit(EXIT_FAILURE);
		}
	}
}

char **sh_split_command(char *);
int sh_execute(char **);

void sh_loop (void)
{
	char *command;
	char **args;
	int status;
	
	do {
		printf("sh> ");
		command = sh_read_command();
		args = sh_split_command(command);
		status = sh_execute(args);
	} while (status);
}

int main ()
{
	int should_run = 1;

	sh_loop();

	return 0;
}
