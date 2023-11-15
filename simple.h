#ifndef SIMPLE_H
#define SIMPLE_H

#include "simple.h"

#define CUSTOM_BUFF_SIZE 1024

#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <ctype.h>

char *custom_strtok(char *string, const char *delim);
ssize_t custom_getline(char **command_buff, size_t *n, FILE *_stdin);

/**
 * struct CustomTokenList - custom tokens list
 * @token: tokens
 * @next: next pointer
*/

typedef struct CustomTokenList
{
	char *token;
	struct CustomTokenList *next;
} CustomTokenNode;

void execute_custom__function(char **arry_tkn, int n,
		char **env, char *command);
void free_and_exit(char **array_token, char **array_paths, char *command);
int custom_setenv(const char *name, const char *value, int overwrite);
char **split_paths(char *paths);
char *custom_trim(char *str);
void custom_free_2d(char **arr_2D);
void custom_env(char **envi, char *command);
void custom_cd(char **command);
void custom_exit_command(char *command);
void handle_comments(char *command);

#endif /* SIMPLE_h */
