#include "simple.h"

/**
 * custom_env - env
 * @envi: env
 * @command: command
 *
 * Return: none
*/

void custom_env(char **envi, char *command)
{
	(void)command;
	while (*envi != NULL)
	{
		printf("%s\n", *envi);
		envi++;
	}
}
