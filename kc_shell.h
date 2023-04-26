/** List of function prototypes for kc_shell by:
 * @DrKayPH
 * @Clement-tech
 * for ALX-SE simple_shell cohort 12 task
 */
#ifndef KC_SHELL_H
#define KC_SHELL_H


int cmd_kc(info_t *, char *);
char *char_d(char *, int, int);
char *pathfinder(info_t *, char *, char *);
int _str_len(char *);
int _str_cmp(char *, char *);
char *_starts_with(const char *, const char *);
char *_str_cat(char *, char *);
char *_strn_cpy(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);


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

int rand_int(int min, int max)
int print_list_reverse(list_t *head)
long int get_file_size(char *filename)
FILE *fp;
int my_unset_alias(info_t *info, char *alias_name)
int _myhistory(info_t *info)
int max_int(int *arr, size_t size)
void print_error(info_t *info, char *estr)
int print_x(unsigned int input, int fd)
double get_array_average(int arr[], int size)
char *string_to_lower(char *str)
char **get_environ(info_t *info)
int _unsetenv(info_t *info, char *var)
int _setenv(info_t *info, char *var, char *value)
list_t *add_node_end(list_t **head, const char *str, int num)
size_t print_list_reverse(const list_t *head)
int delete_node_by_value(list_t **head, const char *value)
void reverse_list(list_t **head)
list_t *add_node(list_t **head, const char *str, int num)
int is_executable(char *file_path)
char *find_executable_path(char *path_env_var, char *command)
void free_array(void **arr, size_t len)
char *_strncpy(char *dest, const char *src, size_t n)
void *_my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
char *starts_with(const char *haystack, const char *needle)
char *_strncat(char *dest, char *src, size_t n)
int _custom_atoi(char *str)
int _custom_strcmp(char *s1, char *s2)
int _custom_strlen(char *str)
int replace_string(char **old, char *new)
int replace_vars(info_t *info)
list_t *node_starts_with(list_t *head, const char *str, char c);
char *convert_number(int num, int base, int is_uppercase);
int replace_alias(info_t *info)
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
int is_chain(info_t *info, char *buf, size_t *p)
int kc_hsh(info_t *info, char **av)
int find_builtin(info_t *info)
void find_cmd(info_t *info)
void my_fork_cmd(info_t *info)
void _eputs(char *str)
int my_putchar(char c, int fd)
int _putfd(char c, int fd)
int _putsfd_kc(char *str, int fd)
char *my_strcpy(char *dest, const char *src)
char *my_strdup(const char *str)
void my_puts(const char *str)
int my_putchar(char c)
char **my_strtow(char *str, char *d)
char **split_string(char *str, char delim)
int is_interactive(info_t *info)
int is_delimiter(char c, const char *delim)
int is_alpha(int c)
int my_atoi(char *s)
int my_exit(info_t *info)
int my_cd(info_t *info)
int myhelp(info_t *info)
ssize_t input_buf(info_t *info, char **buf, size_t *len)
ssize_t get_input(info_t *info)
ssize_t my_read_buf(info_t *info, char *buf, size_t *i)
int my_getline(info_t *info, char **ptr, size_t *length)
void sigintHandler(__attribute__((unused))int sig_num)
void initialize_info(info_t *info)
void initialize_info(info_t *info, char **av)
void cleanup_info(info_t *info, int all)
int print_env(char **envp)
char *my_getenv(char **env, const char *name)
int mysetenv(const char *key, const char *value, int overwrite)
int my_unsetenv(const char *name)
int my_populate_env_list(info_t *info)
char *get_history_file(info_t *info)
int write_history(info_t *info)
int read_history(info_t *info)
int build_history_list(info_t *info, char *buf, int linecount)
int update_history(info_t *info)
size_t my_list_len(const struct node *head)
char **list_to_strings(list_t *head)
size_t print_list(const list_t *h)
list_t *node_starts_with(list_t *node, char *prefix, char c)
int get_node_index_kc(list_t *head, list_t *node)
#endif
