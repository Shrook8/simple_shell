#include "simple.h"

/**
 * handle_comments - comments
 * @command: str
 *
 * Return: depend
*/

void handle_comments(char *command)
{
	int a;

	for (a = 1; command[a] != '\0'; a++)
	{
		if (isspace(command[a - 1]) && command[a] == '#')
		{
			command[a] = '\0';
			break;
		}
	}
}
