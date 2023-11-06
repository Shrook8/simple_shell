#include "shell.h"

int (*get_custom_builtin(char *command))(char **args, char **front);
int custom_shell_exit(char **args, char **front);
int custom_shell_cd(char **args, char __attribute__((__unused__)) **front);
int custom_shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_custom_builtin - matches a command
 * @command: the command
 *
 * Return: pointer
*/

int (*get_custom_builtin(char *command))(char **args, char **front)
{
	custom_builtin_t funcs[] = {
		{ "exit", custom_shell_exit },
		{ "env", custom_shell_env },
		{ "setenv", custom_shell_setenv },
		{ "unsetenv", custom_shell_unsetenv },
		{ "cd", custom_shell_cd },
		{ "alias", custom_shell_alias },
		{ "help", custom_shell_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; funcs[a].name; a++)
	{
		if (_strcmp(funcs[a].name, command) == 0)
			break;
	}
	return (funcs[a].f);
}

/**
 * custom_shell_exit - exit the shell
 * @args: the argument
 * @front: the front
 *
 * Return: depend in what happend
*/

int custom_shell_exit(char **args, char **front)
{
	int a, l = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			a = 1;
			l++;
		}
		for (; args[0][a]; a++)
		{
			if (a <= l && args[0][a] >= '0' && args[0][a] <= '9')
				num = (num * 10) + (args[0][a] - '0');
			else
				return (create_custom_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (custom_create_error(--args, 2));
	args -= 1;
	custom_free_args(arga, front);
	custom_free_env();
	custom_free_alias_list(aliases);
	custom_exit(num);
}

/**
 * custom_shell_cd - cd to the shell
 * @args: the args
 * @front: pointer
 *
 * Return: depend in what happend
*/

int custom_shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = custom_getcwd(oldpwd, 0);
	if (!oldpwd)
	return (-1);
	if (args[0])
	{
		if (*(args[0]) == '-' || custom_strcmp(args[0], "--") == 0)
	{
		if ((args[0][1] == '-' && args[0][2] == '\0') ||
		args[0][1] == '\0')
	{
		if (custom_getenv("OLDPWD") != NULL)
		(custom_chdir(*custom_getenv("OLDPWD") + 7));
	}
	else
	{
		custom_free(oldpwd);
		return (custom_create_error(args, 2));
	}
	}
	else
	{
	if (custom_stat(args[0], &dir) == 0 && custom_S_ISDIR(dir.st_mode) &&
	((dir.st_mode & custom_S_IXUSR) != 0))
	custom_chdir(args[0]);
	else
	{
		custom_free(oldpwd);
		return (custom_create_error(args, 2));
	}
	}
	}
	else
	{
	if (custom_getenv("HOME") != NULL)
		custom_chdir(*custom_getenv("HOME") + 5);
	}
	pwd = custom_getcwd(pwd, 0);
	if (!pwd)
	return (-1);
	dir_info = custom_malloc(sizeof(char *) * 2);
	if (!dir_info)
	return (-1);
	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (custom_shell_setenv(dir_info, dir_info) == -1)
	return (-1);
	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (custom_shell_setenv(dir_info, dir_info) == -1)
	return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		custom_write(STDOUT_FILENO, pwd, custom_strlen(pwd));
		custom_write(STDOUT_FILENO, new_line, 1);
	}
	custom_free(oldpwd);
	custom_free(pwd);
	custom_free(dir_info);
	return (0);
}

/**
 * custom_shell_help - help shell
 * @args: ardes
 * @front: the front
 *
 * Return: depend in what happend
*/

int custom_shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		custom_help_all();
	else if (custom_strcmp(args[0], "alias") == 0)
		custom_help_alias();
	else if (custom_strcmp(args[0], "cd") == 0)
		custom_help_cd();
	else if (custom_strcmp(args[0], "exit") == 0)
		custom_help_exit();
	else if (custom_strcmp(args[0], "env") == 0)
		custom_help_env();
	else if (custom_strcmp(args[0], "setenv") == 0)
		custom_help_setenv();
	else if (custom_strcmp(args[0], "unsetenv") == 0)
		custom_help_unsetenv();
	else if (custom_strcmp(args[0], "help") == 0)
		custom_help_help();
	else
		custom_write(STDERR_FILENO, name, custom_strlen(name));
	return (0);
}