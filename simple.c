#include "simple.h"

/**
 * contains_hash - check the command
 * @command: the command
 *
 * Return: 0 or 1 pr 2 depend in what happend
*/

int contains_hash(char *command)
{
	int a = 1;

	while (command[a])
	{
		if (command[a - 1] == ' ' && command[a] == '#')
			return (2);
		a++;
	}
	return (0);
}

/**
 * exit_shell - exit the shell
 * @status: exit the shell
 * @command: command
 *
 * Return: none
*/

void exit_shell(int status, char *command)
{
	free(command);
	exit(status);
}

/**
 * tokenize_command - yje input
 * @command: command
 *
 * Return: arr of str
*/

char **tokenize_command(char *command)
{
	char *token;
	char **tokens = malloc(CUSTOM_BUFF_SIZE * sizeof(char *));
	int num_tokens = 0, a;

	token = custom_strtok(command, " ");
	if (tokens == NULL || token == NULL)
		return (NULL);
	while (token != NULL)
	{
		tokens[num_tokens] = strdup(token);
		if (tokens[num_tokens] == NULL)
		{
			for (a = 0; a < num_tokens; a++)
				free(tokens[a]);
			free(tokens);
			return (NULL);
		}
		num_tokens++;
		token = custom_strtok(NULL, " ");
	}
	tokens[num_tokens] = NULL;
	return (tokens);
}

/**
 * has_non_space_chars - xcheck the str
 * @command: str
 *
 * Return: 0 or 1 depend in what happend
*/

int has_non_space_chars(char *command)
{
	int counter;
	static size_t space_counter;

	space_counter = 0;
	counter = 0;
	if (command[counter] == ' ')
	{
		while (command[space_counter])
			if (isspace((unsigned char)command[space_counter]))
				space_counter++;
			else
				break;
		counter++;
	}
	if (space_counter == strlen(command))
		return (0);
	return (1);
}

/**
 * main - main fun
 * @argc: arg count
 * @argv: arg vector
 * @env: env
 *
 * Return: fail -1, success 0
*/

int main(int argc, char **argv, char **env)
{
	char *command_buffer = malloc(CUSTOM_BUFF_SIZE * sizeof(char)),
	     *trimmed, **token_array;
	size_t buffer_size = CUSTOM_BUFF_SIZE, a;
	(void)argc;
	(void)argv;

	while (1)
	{
		fflush(stdout);
		if (custom_getline(&command_buffer, &buffer_size, stdin) == -1)
			exit_shell(0, command_buffer);
		if (has_non_space_chars(command_buffer) == 0 || command_buffer[0] == '#')
			continue;
		else if (contains_hash(command_buffer) == 2)
			handle_comments(command_buffer);
		trimmed = custom_trim(command_buffer);
		if (trimmed == NULL)
		{
			free(command_buffer);
			continue;
		}
		if (strcmp(trimmed, "env") == 0)
		{
			custom_env(env, command_buffer);
			continue;
		}
		else if (strncmp(trimmed, "exit", 4) == 0)
			custom_exit_command(command_buffer);
		token_array = tokenize_command(trimmed);
		if (token_array != NULL)
		{
			for (a = 0; token_array[a] != NULL; a++)
				continue;
			execute_custom_function(token_array, a, env, command_buffer);
			custom_free_2d(token_array);
		}
	}
	free(command_buffer);
	return (0);
}
