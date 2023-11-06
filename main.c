#include "shell.h"
#include <signal.h>

void handle_signal(int signal);
int run_command(char **arguments, char **front);

/**
 * handle_signal - handle signal and print new promot
 * @signal: the signal
 *
 * Return: nothing
*/

void handle_signal(int signal)
{
	char *new_prompt = "\n$ ";

	(void)signal;
	signal(SIGINT, handle_signal);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * run_command - executes a command
 * @arguments: array of command
 * @front: double pointer
 *
 * Return: if error occurs otherwise exit
*/

int run_command(char **arguments, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = arguments[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(arguments, 126));
		else
			ret = (create_error(arguments, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Child process error:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, arguments, environ);
			if (errno == EACCES)
				ret = (create_error(arguments, 126));
			free_env();
			free_args(arguments, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
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
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, handle_signal);
	*exe_ret = 0;
	environ = copy_environment();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		ret = process_file_commands(argv[1], exe_ret);
	free_environment();
	free_alias_list(aliases);
	return (*exe_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
	while (ret != END_OF_FILE && ret != EXIT)
	ret = handle_args(exe_ret);
	free_environment();
	free_alias_list(aliases);
	return (*exe_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
	ret = handle_args(exe_ret);
	if (ret == END_OF_FILE || ret == EXIT)
	{
	if (ret == END_OF_FILE)
	write(STDOUT_FILENO, new_line, 1);
	free_environment();
	free_alias_list(aliases);
	exit(*exe_ret);
	}
	}
	free_environment();
	free_alias_list(aliases);
	return (*exe_ret);
}
