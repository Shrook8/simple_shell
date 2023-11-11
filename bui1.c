#include "shell.h"

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

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "type 'helep' to see the list.\n type 'help name' to find";
	write(STDOUT_FILENO, msg,_strlen(msg));
	msg = "out more about the function 'name'.\n alias \t";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
