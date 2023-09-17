#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

#define BUFFER_SIZE 50


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096




/**
 * struct nodestr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct nodestr
{
	int num;
	char *str;
	struct nodestr *next;
} node_t;

/**
 * struct codeinfo - contain arguements to pass into a function,
 * @cmd_buf: pointer to pointer char
 * @histcount: line count of the history
 * @read_file_descriptor: file descriptor to read
 * @cmd_buf_type: CMD type
 * @environ: pointer to pointer modified environ copy
 * @arg: a string generated from getline containing arguements
 * @status: last executed command status
 * @env_changed: display on when environ changed
 * @argc: argument count
 * @argv: argument vector
 * @path: pointer to string path to the current command
 * @alias: alias node
 * @env: environ linked list
 * @history: history node
 * @fname: filename
 * @err_num: error msg
 * @line_count: the error count
 * @linecount_flag: count line if on
 */
typedef struct codeinfo
{
	char **cmd_buf;
	int histcount;
	int read_file_descriptor;
	int cmd_buf_type;
	char **environ;
	int status;
	int env_changed;
	int argc;
	char **argv;
	char *path;
	char *arg;
	node_t *alias;
	node_t *env;
	node_t *history;
	char *fname;
	int err_num;
	int linecount_flag;
	unsigned int line_count;
} code_t;

#define INFO_INIT \
{NULL, 0, 0, 0, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
			0, 0, 0}

/**
 * struct command - contain command string and related function
 * @type: command flag
 * @func: function
 */
typedef struct command
{
	char *type;
	int (*func)(code_t *);
} command_list;

void fork_command(code_t *info);
void command_path(code_t *info);
int hsh(code_t *info, char **argv);

void code_set(code_t *info, char **av);
void code_clear(code_t *info);
void code_free(code_t *info, int all);

size_t list_print(const node_t *f);
ssize_t node_index_get(node_t *head, node_t *node);
size_t length_list(const node_t *f);
node_t *node_begin_with_prefix(node_t *node, char *prefix, char c);
char **string_list(node_t *head);

char *custom_memset(char *s, char b, unsigned int n);
void string_free(char **ptr);
int memory_free(void **ptr);
void *custom_realloc(void *ptr, unsigned int o_size, unsigned int n_size);



/* loophsh.c */
int loophsh(char **);

int custom_put_fd(char c, int fd);
int custom_puts_fd(char *str, int fd);
int custom_putchar(char c);
void custom_puts(char *str);
int custom_error_atoi(char *str);
int print_decimal(int input, int fd);
void custom_print_error(code_t *info, char *str);
void replace_instance(char *str);
char *convert_to_number(long int num, int base, int flags);

char *custom_strchr(char *str, char c);
char *custom_strncat(char *dest, char *src, int n);
char *custom_strncpy(char *dest, char *src, int n);
char *custom_strcpy(char *dest, char *src);
char *custom_strdup(const char *str);
int _putchar(char c);
void _puts(char *str);
char *starts_check(const char *haystack, const char *needle);
int custom_strlen(char *str);
char *custom_strcat(char *dest, char *src);
int custom_strcmp(char *str1, char *str2);

char **string_to_word(char *str, char delimeter);
char **custom_strtow(char *str, char *delimeter);

void chain_check(code_t *info, char *buffer,
		size_t *ptr, size_t n, size_t length);
int string_replace(char **old, char *neew);
int variable_replace(code_t *info);
int alias_replace(code_t *info);
int chain_test(code_t *info, char *buffer, size_t *ptr);

char *get_history(code_t *info);
int reset_history(code_t *info);
int history(code_t *info);
int add_history(code_t *info, char *buffer, int count);
int create_history(code_t *info);

node_t *create_node(node_t **head, const char *str, int num);
node_t *create_node_end(node_t **head, const char *str, int num);
int node_index_delete(node_t **head, unsigned int index);
void node_free_list(node_t **head_p);
size_t liststr_print(const node_t *f);

int command_exec(code_t *info, char *path);
char *character_duplicate(char *strpath, int begin, int stop);
char *path_search(code_t *info, char *strpath, char *cmd);
int command_find(code_t *info);

ssize_t buffer(code_t *info, char *buffer, size_t *n);
int custom_getline(code_t *info, char **pt, size_t *len);
ssize_t buffer_command(code_t *info, char **buffer, size_t *length);
ssize_t get_line(code_t *info);
void sigintHandler(__attribute__((unused))int signal_number);

int ascii_to_integer(char *s);
int is_alphabet(int c);
int delimiter_check(char c, char *delimiter);
int check_interactive(code_t *info);


int custom_alias_unset(code_t *info, char *str);
int custom_alias_set(code_t *info, char *str);
int custom_alias_print(node_t *node);
int custom_alias(code_t *info);
int custom_cd(code_t *info);
int custom_history(code_t *info);
int custom_help(code_t *info);
int custom_exit(code_t *info);

int custom_setenv(code_t *info, char *var, char *value);
int custom_unsetenv(code_t *info, char *var);
int custom_set_environ(code_t *info);
int custom_unset_environ(code_t *info);
int custom_environ(code_t *info);
char *custom_get_environ(code_t *info, const char *name);
int custom_print_environ(code_t *info);
char **custom_environ_get(code_t *info);



#endif
