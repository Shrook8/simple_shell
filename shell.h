#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define EOF_MAKER -2
#define EXIT_CODE -3
#define END_OF_FILE 1
#define EXIT 2


extern char **environ;
extern char *name;
extern int hist;

/**
 * struct PathNode -  a struct for def linked list node
 * @path: dir path
 * @next: pointer to the next struct PathNode
 *
 * Return: none
*/

typedef struct PathNode
{
	char *path;
	struct PathNode *next;
} PathNode;

/**
 * struct BuiltinCommand - a struct for def builtin commands
 * @name: the name
 * @function: a function pointer
*/

typedef struct BuiltinCommand
{
	char *name;
	int (*function)(char **arguments, char **front);
} BuiltinCommand;

/**
 * struct Alias - a struct for def aliases
 * @name: the name of the alias
 * @value: the value
 * @next: a pointer
*/

typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

/* global aliases */

Alias *alias_list;


/* main */

void handle_signal(int *signal);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **custom_strtok(char *line, char *delimiters);
char *custom_get_command_location(char *command);
PathNode *custom_get_path_directories(char *path);
int custom_execute_command(char **arguments, char **front);
void custom_free_path_list(PathNode *head);
char *custom_int_to_string(int number);

/* input */

void process_input_line(char **line, ssize_t read);
void replace_variables(char **arguments, int *execution_result);
char *get_input_arguments(char *line, int *execution_result);
int process_arguments(char **arguments, char **front, int *execution_result);
int run_command_arguments(char **arguments, char **front,
		int *execution_result);
int handle_command_arguments(int *execution_result);
int check_command_arguments(char **arguments);
void free_command_arguments(char **arguments, char **front);
char **replace_aliases_in_arguments(char **arguments);

/* str functions */

int custom_strlen(const char *string);
char *custom_strcat(char *destination, const char *source);
char *custom_strncat(char *destination, const char *source, size_t num);
char *custom_strcpy(char *destination, const char *source);
char *custom_strchr(char *string, char character);
int custom_strspn(char *string, char *accept);
int custom_strcmp(char *string1, char *string2);
int custom_strncmp(const char *string1, const char *string2, size_t num);

/* builtin */

int (*get_custom_builtin(char *command))(char **args, char **front);
int custom_env(char **arguments, char __attribute__((__unused__)) **front);
int custom_setenv(char **arguments, char __attribute__((__unused__)) **front);
int custom_unsetenv(char **args, char **front);
int custom_change_directory(char **arguments,
		char __attribute__((__unused__)) **front);
int custom_alias(char **arguments, char __attribute__((__unused__)) **front);
int custom_help(char **args);

int (*get_custom_builtin(char *command))(char **arguments, char **front);
int custom_shell_exit(char **args);
int custom_shell_cd(char **args);
int custom_help(char **arguments, char **front);
void custom_free_path_list(PathNode *head);

/* builtin h */

char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *variable);

/* error handling */

int generate_error(char **arguments, int error_code);
char *error_for_env(char **arguments);
char *error_for_code_1(char **arguments);
char *error_for_code_2_exit(char **arguments);
char *error_for_code_2_cd(char **arguments);
char *syntax_error(char **arguments);
char *error_for_code_126(char **arguments);
char *error_for_code_127(char **arguments);

/* linkedlist */

void free_alias_list(Alias *head);
PathNode *add_path_node_to_list(PathNode **head, char *directory);
void free_path_list(PathNode *head);
void display_all_help(void);
void display_alias_help(void);
void display_cd_help(void);
void display_exit_help(void);
void display_help_help(void);
void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);
void display_history_help(void);
int process_file_commands(char *file_path, int *execution_result);

#endif /* _SHELL_H_ */
