#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void parse_input(char *input, char **args)
{
	int i = 0;

	args[i] = strtok(input, " \t\n");
	while (args[i] != NULL)
	{
	i++;
	args[i] = strtok(NULL, " \t\n");
	}
}

void custom_shell_cd(char **args)
{
	if (args[1] == NULL)
	{
	fprintf(stderr, "cd: missing argument\n");
	}
	else
	{
	if (chdir(args[1]) != 0)
	{
	perror("cd");
	}
	}
}

void custom_shell_exit(void)
{
	exit(0);
}

void custom_shell_help(void)
{
	printf("Custom Shell - Basic Commands:\n");
	printf("1. cd [directory] - Change current directory\n");
	printf("2. exit - Exit the shell\n");
	printf("3. help - Display this help message\n");
}

void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("custom_shell");
		}
		exit(1);
	}
	else if (pid < 0)
	{
		perror("custom_shell");
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_ARG_SIZE];

	while (1)
	{
	printf("Custom Shell > ");
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
	break;
	}
	parse_input(input, args);
	if (args[0] == NULL)
	{
	continue;
	}
	if (strcmp(args[0], "cd") == 0)
	{
	custom_shell_cd(args);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
	custom_shell_exit();
	}
	else if (strcmp(args[0], "help") == 0)
	{
	custom_shell_help();
	}
	else
	{
		execute_command(args);
	}

	return (0);
}

