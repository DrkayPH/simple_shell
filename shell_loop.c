#include "kc_shell.h"

/**
 * kc_hsh - kc shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int kc_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			printf("$ ");
		fflush(stdout);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *          -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;

    // Define a struct to hold the builtin commands and their associated functions.
    typedef struct {
        char *name;
        int (*func)(info_t *);
    } builtin_t;

    // Define an array of builtin commands and their associated functions.
    builtin_t builtins[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    // Iterate over the array of builtin commands, and execute the corresponding function if a match is found.
    for (i = 0; builtins[i].name; i++) {
        if (_strcmp(info->argv[0], builtins[i].name) == 0) {
            info->line_count++;
            built_in_ret = builtins[i].func(info);
            break;
        }
    }

    // Return the result of executing the matched builtin command.
    return built_in_ret;
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    // Set the path to the first argument by default
    info->path = info->argv[0];

    // Increment line count if linecount flag is set
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    // Count the number of non-delimiter arguments
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!is_delim(info->arg[i], " \t\n"))
        {
            k++;
        }
    }

    // Return if no non-delimiter arguments were found
    if (!k)
    {
        return;
    }

    // Find the command in PATH
    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    // If the command was found in PATH, update the path and fork the command
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    // If the command was not found in PATH, check if it is an absolute path or a valid command in the current directory
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
        {
            fork_cmd(info);
        }
        else if (*(info->arg) != '\n')
        {
            // If the command was not found and is not an absolute path or a valid command, set the status to 127 and print an error message
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * my_fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void my_fork_cmd(info_t *info)
{
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();
    if (child_pid == -1)
    {
        // Handle the error if forking fails
        perror("Error:");
        return;
    }

    if (child_pid == 0)
    {
        // Child process
        char **environ = get_environ(info);
        if (execve(info->path, info->argv, environ) == -1)
        {
            // Handle the error if execve fails
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        // Parent process
        int status;
        pid_t wait_pid = waitpid(child_pid, &status, 0);
        if (wait_pid == -1)
        {
            // Handle the error if waitpid fails
            perror("Error:");
            return;
        }

        // Check the exit status of the child process
        if (WIFEXITED(status))
        {
            info->status = WEXITSTATUS(status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}

