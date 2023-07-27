#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_LINE 80
#define BUFFER_SIZE 1024
#define ARG_SIZE 64
#define DELIM " \t\n\a\r"

char *last_command = NULL;

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
			if (strcmp("!!", buffer) != 0) {
				last_command = malloc(sizeof(char) * size);
				strcpy(last_command, buffer);
			}
			return buffer;
		} else {
			buffer[position] = ch;
		}
		position++;
		if (position >= size) {
			size += BUFFER_SIZE;
			buffer = realloc(buffer, size);
			if (!buffer) {
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **sh_split_command (char *command)
{
	int size = ARG_SIZE;
	int position = 0;
	char **args = malloc(sizeof(char *) * size);
	char *arg;

	if (!args) {
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	arg = strtok(command, DELIM);
	while (arg != NULL) {
		args[position] = arg;
		position++;
		if (position >= size) {
			size += ARG_SIZE;
			args = realloc(args, size);
			if (!args) {
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		arg = strtok(NULL, DELIM);
	}
	args[position] = NULL;
	return args;
}

int sh_execute (char **args)
{
	pid_t pid, wpid;
	  int status;

	  pid = fork();
	  if (pid == 0) {
	    if (execvp(args[0], args) == -1) {
	      perror("sh");
	    }
	    exit(EXIT_FAILURE);
	  } else if (pid < 0) {
	    perror("lsh");
	  } else {
	    do {
	      wpid = waitpid(pid, &status, WUNTRACED);
	    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	  }

	  return 1;
}

void sh_loop (void)
{
	char *command;
	char **args;
	int status;

	do {
		printf("sh> ");
		command = sh_read_command();
		if (strcmp(command, "!!") == 0) {
			if (last_command == NULL) {
				printf("No History!\n");
				status = 1;
				continue;
			}
			args = sh_split_command(last_command);
			status = sh_execute(args);
			continue;
		}
		args = sh_split_command(command);
		status = sh_execute(args);
	} while (status);
}

int main ()
{
	sh_loop();
	return 0;
}
