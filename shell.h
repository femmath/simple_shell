#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/**
 * struct liststr – called a singly linked list
 * @num: the var to link
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo – pass arguements to a function,
 * for uniform prototype of function pointer struct
 * @arg: getline strings containing args
 * @argv: array of strings 
 * @path: the path for the current command
 * @argc: argument count
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd where line input is to be read
 * @histcount: the history line count
 * @line_count: line count
 * @linecount_flag: status flag for line count
 * @err_num: the error code specifier
 * @environ: modified copy of env 
 * @history: the history node
 * @alias: the alias node
 * @fname: the filename
 * @env: local copy of linked list environ
 * @env_changed: check if environ was changed
 * @status: status of the last executed command
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	char *fname;
	list_t *env;
	list_t *history;
        int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	int status;
	list_t *alias;
	char **environ;
	int env_changed;
	int histcount;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	
}

/**
 * struct builtin - builtin string 
 * @func: the function
 * @type:  builtin command flag
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}

int hsh(info_t *, char **);
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
void _eputs(char *);
int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);
char _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
int bfree(void **);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);
void print_error(info_t *, char *);
void print_d(int, int);
int _erratoi(char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
int delete_node_at_index(list_t **, unsigned int);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);


#endif

