#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - the main
 *
 * Return: nothing
*/

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
	return (0);

}
