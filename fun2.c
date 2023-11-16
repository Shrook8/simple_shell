#include "simple.h"

/**
 * child_process - process
 * @arry_tkn: array
 * @env: env
 * @command: command
 *
 * Return: none
*/

void child_process(char **arry_tkn, char **env, char *command)
{
	char *con_path;

	if (arry_tkn[0][0] == '/' || arry_tkn[0][0] == '.')
	{
		if (execve(arry_tkn[0], arry_tkn, env) == -1)
			handle_execution_error(arry_tkn, paths, command);
	}
	else
	{
		con_path = find_correct_path(arry_tkn, paths);
		if (execve(con_path, arry_tkn, env) == -1)
			handle_execution_error(arry_tkn, paths, command);
	}
	exit(EXIT_FAILURE);
}

/**
 * parent_process - parent
 * @pid: pid
 * @arry_tkn: array
 * @paths: paths
 * @command: command
 *
 * Return: none
*/

void parent_process(pid_t pid, char **arry_tkn, char **paths, char *command)
{
	int status, exit_status;

	if (waitpid(pid, &status, 0) == -1)
		exit(EXIT_FAILURE);
	exit_status = WEXITSTATUS(status);
	if (exit_status == 2)
		free_and_exit(arry_tkn, paths, command);
}

/**
 * execute_custom_function - executes
 * @arry_tkn: array
 * @n: num
 * @env: env
 * @command: command
 *
 * Return: none
*/

void execute_custom__function(char **arry_tkn, int n,
		char **env, char *command)
{
	pid_t pid;
	char *path, **paths;

	path = get_path_directories(env);
	paths = split_paths(paths);
	arry_tkn[n] = NULL;
	if (is_valid_command(arry_tkn, paths) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			child_process(arry_tkn, env, command);
		}
		else if (pid < 0)
		{
			handle_execution_error(arry_tkn, paths, command);
		}
		else
		{
			parent_process(pid, arry_tkn, paths, command);
		}
	}
	else
	{
		handle_execution_error(arry_tkn, paths, command);
	}
	custom_free_2d(paths);
}
