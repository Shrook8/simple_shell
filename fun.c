#include "simple.h"

/**
 * handle_execution_error - handles errors
 * @argv: command
 * @paths: paths
 * @command: command
 *
 * Return: none
*/

void handle_execution_error(char **argv, char **paths, char *command)
{
	int a = 0;

	while (argv[a])
	{
		fprintf(stderr, "./custom_shell: 1: %s: not fount\n", argv[a]);
		a++;
	}
	custom_free_2d(argv);
	custom_free_2d(paths);
	free(command);
	exit(127);
}

/**
 * find_correct_path - finds the correct path
 * @argv: command
 * @paths: paths
 *
 * Return: path
*/

char *find_correct_path(char **argv, char **paths)
{
	char *con_path;
	int a;
	size_t concat_size;

	for (a = 0; paths[a] != NULL; a++)
	{
		concat_size = strlen(paths[a]) + strlen("/") + strlen(argv[0]) + 1;
		con_path = malloc(concat_size);
		if (con_path == NULL)
			return (NULL);
		strcpy(con_path, paths[a]);
		strcat(con_path, "/");
		strcat(con_path, argv[0]);
		if (access(con_path, F_OK) == 0)
			return (con_path);
		free(con_path);
	}
	return (NULL);
}


/**
 * get_path_directories - ret path dir
 * @env: env
 *
 * Return: str
*/

char *get_path_directories(char **env)
{
	while (*env != NULL)
	{
		if (strncmp(*env, "PATH", 4) == 0)
			return (strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}


/**
 * is_valid_command - checks the valid command
 * @argv: command
 * @paths: paths
 *
 * Return: depend
*/

int is_valid_command(char **argv, char **paths)
{
	char *char *con_path = find_correct_path(argv, paths);

	if (argv[0] == NULL)
		return (0);
	if (access(argv[0], F_OK) == 0)
		return (1);
	else if (con_path)
	{
		free(con_path);
		return (1);
	}
	return (-1);
}
