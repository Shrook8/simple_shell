#include "simple.h"

/**
 * custom_trim - trim
 * @str: str
 *
 * Return: str
*/

char *custom_trim(char *str)
{
	char *e;

	while (isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	e = str + strlen(str) - 1;
	while (e > str && isspace((unsigned char)*e))
		e--;
	*(e + 1) = '\0';
	return (str);
}
