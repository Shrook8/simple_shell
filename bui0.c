#include "shell.h"

void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);

/**
 * display_env_help - display duitin command env
*/

void display_env_help(void)
{
	char *m = "env: env\n\t print the current env\n;

	write(STDOUT_FILENO, m, _strlen(m));
}

/**
 * display_unsetenv_help - display builtin command unsetenv
*/

void display_unsetenv_help(void)
{
	char *m = "unsetenv: unsetenv [VARIABLE]\n\t Removes an ";

	write(STDOUT_FILENO, m, _strlen(msg));
	m = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "message to stderr.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}

/**
 * display_setenv_help - display builtin command setenv
*/

void display_setenv_help(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "\t Upon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
