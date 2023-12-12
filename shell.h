#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>



/* Pertaining to buffers used for reading and writing operations */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

/* for command chaining */
#define CMD_AND		2
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* 1 if using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 *  struct liststr - singly linked list structure
 * @num: numerical field within the structure
 * @str: a string held within the structure
 * @next: reference to the subsequent node in the list
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;
/**
*struct passinfo - encapsulates pseudo-arguments for passing into a function,
*@arg: a string generated from getline containing arguments
*@argv: an array of strings generated from arg
*@path: a string representing the current command's path
*@argc: the count of arguments
*@line_count: the count of lines (errors)
*@err_num: the error code for exit() calls
*@linecount_flag: flag indicating whether to count this line of input
*@fname: the filename of the program
*@env: local linked list copy of the environment variables
*@environ: custom modified copy of the environment from the LL env
*@history: the history node
*@alias: the alias node
*@env_changed: flag indicating if environ was modified
*@status: the return status of the last executed command
*@cmd_buf: address of pointer to cmd_buf, set if chaining commands
*@cmd_buf_type: CMD_type ||, &&, ;
*@readfd: the file descriptor from which to read line input
*@histcount: the history line number count
*/
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

/* Pointer to the command chaining buffer for efficient memory management */
char **cmd_buf;

/*Command type ||, &&, ; */
int cmd_buf_type;

int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
*struct builtin - holding information about a built-in command, including its
*	string representation and associated function pointer.
*@type: Builtin command information structure containing a flag for the
*	command type
*@func: a function pointer to its associated function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int find_builtin(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _putfd(char k, int filedesc);
int _putsfd(char *str, int fd);
int _eputchar(char);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);
char *_strdup(const char *);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);

/* toem_errors1.c */
char *convert_number(long int, int, int);
void print_error(info_t *, char *);
int print_d(int, int);
void remove_comments(char *);
int _erratoi(char *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int print_alias(list_t *);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);
void sigintHandler(__attribute__((unused)) int);
ssize_t get_input(info_t *);


/* toem_getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/* toem_environ.c */
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
char *_getenv(info_t *, const char *);
int _myunsetenv(info_t *);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* toem_history.c */
int write_history(info_t *inform);
int read_history(info_t *inform);
char *get_history_file(info_t *inform);
int build_history_list(info_t *inform, char *buff, int linecount);
int renumber_history(info_t *inform);

/* toem_lists.c */
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);

/* toem_lists1.c */
size_t print_list(const list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


/* toem_main.c*/
int main(int, char **);

#endif
