#include "simple.h"

/**
 * free_and_exit - exit
 * @array_token: token
 * @array_paths: paths
 * @command: command
 *
 * Return:none
*/

void free_and_exit(char **array_token, char **array_paths, char *command)
{
	if (array_token != NULL)
		custom_free_2d(array_token);
	if (array_paths != NULL)
		custom_free_2d(array_paths);
	if (command != NULL)
		free(command);
	exit(2);
}
