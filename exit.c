#include "simple.h"

/**
 * is_valid_exit_status - exit the shell
 * @str: input str
 *
 * Return: 0, 1 depend
*/

int is_valid_exit_status(char *str)
{
	int a = 0;

	if (str[0] == '-')
		return (0);

	for (; str[a] != '\0'; a++)
	{
		if (str[a] < '0' || str[a] > '9')
			return (0);
	}
	return (1);
}

/**
 * custom_exit_command - exit the shell
 * @command: command
 *
 * Return: exit
*/

void custom_exit_command(char *command)
{
	char *status_str = strchr(command, ' ');
	int exit_status;

	if (strcmp(command, "exit") == 0)
	{
		free(command);
		exit(0);
	}
	if (status_str != NULL)
	{
		status_str++;

		if (is_valid_exit_status(status_str))
			exit_status = atoi(status_str);
		else
		{
			fprintf(stderr, "./custom_shell: exit: Illegal number: %s\n", status_str);
			free(command);
			exit(2);
		}
		free(command);
		exit(exit_status);
	}
	free(command);
}
