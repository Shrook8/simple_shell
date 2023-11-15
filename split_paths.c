#include "simple.h"


/**
 * split_paths - split paths
 * @paths: paths
 *
 * Return: split paths
*/

char **split_paths(char *paths)
{
	char *token;
	char **tokens = malloc(BUFF_SIZE * sizeof(char *));
	int n = 0, a;
	char *paths_copy;

	paths_copy = strdup(paths);
	if (tokens == NULL || paths_copy == NULL)
		return (NULL);
	token = custom_strtok(paths_copy, ":");
	while (token != NULL)
	{
		tokens[n] = strdup(token);
		if (tokens[n] == NULL)
		{
			for (a = 0; a < n; a++)
				free(tokens[a]);
			free(tokens);
			free(paths_copy);
			return (NULL);
		}
		n++;
		token = custom_strtok(NULL, ":");
	}
	tokens[n] = NULL;
	free(paths_copy);
	return (tokens);
}
