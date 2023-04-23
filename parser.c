#include "kc_shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(char *file_path)
{
	struct stat st;

	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
		return (1);

	return (0);
}

/**
 * find_executable_path - finds the path to an executable file in the PATH
 * environment variable
 * @path_env_var: the PATH environment variable
 * @command: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_executable_path(char *path_env_var, char *command)
{
	char *path_env_var_copy, *path, *token, *executable_path;
	size_t path_len, command_len;

	path_env_var_copy = strdup(path_env_var);
	path_len = strlen(path_env_var_copy);
	command_len = strlen(command);

	if (path_env_var_copy[path_len - 1] != '/')
		path_env_var_copy[path_len] = '/';
	path_env_var_copy[path_len + 1] = '\0';

	token = strtok(path_env_var_copy, ":");
	while (token)
	{
		path = strdup(token);
		executable_path = malloc(strlen(path) + command_len + 1);
		strcpy(executable_path, path);
		strcat(executable_path, command);
		if (is_executable(executable_path))
		{
			free(path_env_var_copy);
			free(path);
			return (executable_path);
		}
		free(executable_path);
		free(path);
		token = strtok(NULL, ":");
	}

	free(path_env_var_copy);
	return (NULL);
}

