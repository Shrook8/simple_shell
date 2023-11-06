#include "shell.h"
#include <signal.h>

void signal_handler(int signal);
int execute_command(char **args, char **front);

/**
 * signal_handler - handle signal and print new promot
 * @signal: the signal
 *
 * Return: nothing
*/

void signal_handler(int signal)
{
	(void)signal;
	write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * execute_command - executes a command
 * @arguments: array of command
 * @front: double pointer
 *
 * Return: if error occurs otherwise exit
*/

int execute_command(char **args, char **front)
{
	pid_t child_pid;
	int status, is_external = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		is_external = 1;
		command = custom_get_command_location(command);
	}
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (generate_error(args, 126));
		else
			ret = (generate_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (is_external)
				free(command);
			perror("Fork error:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (generate_error(args, 126));
			free_environment();
			free_command_arguments(args, front);
			free_alias_list(alias_list);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (is_external)
		free(command);
	return (ret);
}

/**
 * main - simple unix command
 * @argc: the num of argc
 * @argv: sarray of pointers
 *
 * Return: last executed command
*/

int main(int argc, char *argv[])
{
	int ret = 0, exe_ret = 0;
	char *prompt = "$ ", *new_line = "\n";
	char *args[] = {NULL};

	name = argv[0];
	hist = 1;
	alias_list = NULL;
	signal(SIGINT, signal_handler);
	exe_ret = 0;
	environ = copy_environment();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		ret = process_file_commands(argv[1], &exe_ret);
	free_environment();
	free_alias_list(alias_list);
	return (exe_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
	while (ret != END_OF_FILE && ret != EXIT)
	ret = execute_command(args, NULL);
	free_environment();
	free_alias_list(alias_list);
	return (exe_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
	ret = execute_command(args, NULL);
	if (ret == END_OF_FILE || ret == EXIT)
	{
	if (ret == END_OF_FILE)
	write(STDOUT_FILENO, new_line, 1);
	free_environment();
	free_alias_list(alias_list);
	exit(exe_ret);
	}
	}
	free_environment();
	free_alias_list(alias_list);
	return (exe_ret);
}
