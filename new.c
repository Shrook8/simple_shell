#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

/**
 * parse_input - input parses
 * @input: the input
 * @args: the arguments
 *
 * Return: nothing
*/

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

/**
 * custom_shell_cd - the cd of the shell
 * @args: the arguments
 *
 * Return: nothing
*/

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

/**
 * custom_shell_exit - exiting the shell
 *
 * Return: nothing
*/

void custom_shell_exit(void)
{
	exit(0);
}

/**
 * custom_shell_help - helping
 *
 * Return: nothing
*/

void custom_shell_help(void)
{
	printf("Custom Shell - Basic Commands:\n");
	printf("1. cd [directory] - Change current directory\n");
	printf("2. exit - Exit the shell\n");
	printf("3. help - Display this help message\n");
}

/**
 * execute_command - command
 * @args: the arguments
 *
 * Return: nothing
*/

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
