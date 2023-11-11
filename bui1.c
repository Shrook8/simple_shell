#include "shell.h"
#include <string.h>

void display_all_help(void);
void display_alias_help(void);
void display_cd_help(void);
void display_exit_help(void);
void display_help_help(void);

/**
 * display_all_help - display builtin
*/

void display_all_help(void)
{
	char *msg = "shellby\n these shell cmmands are defined internally.\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "type 'helep' to see the list.\n type 'help name' to find";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "out more about the function 'name'.\n alias \t";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * display_alias_help - display buitin command alias
*/

void display_alias_help(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\t handles aliases\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n\t alias: prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "the format NAME='VALUE'.\n\t alias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * display_help_help - display builtin command help
*/

void display_help_help(void)
{
	char *msg = "help: help\n\tSee all possible shell by builtin commands.\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * display_exit_help - display builtin command exit
*/

void display_exit_help(void)
{
	char *msg = "exit: exit [STATUS]\n\texits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}


/**
 * display_cd_help - display builtin command cd
*/


void display_cd_help(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tchanges the current directory of the";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}
