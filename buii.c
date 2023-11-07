#include "shell.h"

int custom_shell_exit(char **args);
int custom_shell_cd(char **args);
int custom_shell_help(char **args);


/**
 * get_custom_builtin - matches a command
 * @command: the command
 *
 * Return: pointer
*/

int (*get_custom_builtin(char *command))(char **args)
{
	struct custom_builtin_t
	{
		const char *name;
		int (*func)(char **args);
	};
	
	struct custom_builtin_t funcs[] = {
		{ "exit", custom_shell_exit },
		{ "cd", custom_shell_cd },
		{ "help", custom_shell_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; funcs[a].name; a++)
	{
		if (_strcmp(funcs[a].name, command) == 0)
	{
			return (funcs[a].func;
	}
	}
	return (NULL);
}

/**
 * custom_shell_exit - exit the shell
 * @args: the argument
 *
 * Return: depend in what happend
*/

int custom_shell_exit(char **args)
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
	custom_free_args(args, front);
	custom_unsetenv();
	custom_free_path_list(Alias);
	custom_exit(num);
}

/**
 * custom_shell_cd - cd to the shell
 * @args: the args
 *
 * Return: depend in what happend
*/

int custom_shell_cd(char **args)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = custom_cd(oldpwd, 0);
	if (!oldpwd)
	return (-1);
	if (args[0])
	{
		if (*(args[0]) == '-' || custom_strcmp(args[0], "--") == 0)
	{
		if ((args[0][1] == '-' && args[0][2] == '\0') ||
		args[0][1] == '\0')
	{
		if (custom_setenv("OLDPWD") != NULL)
		(custom_cd(*custom_setenv("OLDPWD") + 7));
	}
	else
	{
		custom_cd(oldpwd);
		return (custom_create_error(args, 2));
	}
	}
	else
	{
	if (custom_strcat(args[0], &dir) == 0 && custom_S_ISDIR(dir.st_mode) &&
	((dir.st_mode & custom_S_IXUSR) != 0))
	custom_cd(args[0]);
	else
	{
		custom_cd(oldpwd);
		return (custom_create_error(args, 2));
	}
	}
	}
	else
	{
	if (custom_setenv("HOME") != NULL)
		custom_cd(*custom_setenv("HOME") + 5);
	}
	pwd = custom_cd(pwd, 0);
	if (!pwd)
	return (-1);
	dir_info = custom_realloc(sizeof(char *) * 2);
	if (!dir_info)
	return (-1);
	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (custom_shell_help(dir_info, dir_info) == -1)
	return (-1);
	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (custom_shell_help(dir_info, dir_info) == -1)
	return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		custom_exit(STDOUT_FILENO, pwd, custom_strlen(pwd));
		custom_exit(STDOUT_FILENO, new_line, 1);
	}
	custom_cd(oldpwd);
	custom_cd(pwd);
	custom_free(dir_info);
	return (0);
}

/**
 * custom_shell_help - help shell
 * @args: ardes
 *
 * Return: depend in what happend
*/

int custom_shell_help(char **args)
{
	if (!args[0])
		custom_help();
	else if (custom_strcmp(args[0], "alias") == 0)
		custom_alias();
	else if (custom_strcmp(args[0], "cd") == 0)
		custom_shell_cd();
	else if (custom_strcmp(args[0], "exit") == 0)
		custom_shell_exit();
	else if (custom_strcmp(args[0], "env") == 0)
		custom_env();
	else if (custom_strcmp(args[0], "setenv") == 0)
		custom_setenv();
	else if (custom_strcmp(args[0], "unsetenv") == 0)
		custom_unsetenv(char **args, char **front);
	else if (custom_strcmp(args[0], "help") == 0)
		custom_shell_help(char **args);
	else
		custom_exit(STDERR_FILENO, name, custom_strlen(name));
	return (0);
}
