#include "kc_shell.h"

/**
 * my_exit - exits the program with a given status code
 * @info: pointer to a structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: exits with a given exit status, 0 if no arguments provided.
 */
int my_exit(info_t *info)
{
  int exit_status = 0;

  if (info->argv[1] != NULL) { // If there is an exit argument
    int exit_code = _erratoi(info->argv[1]); // Convert the argument to an integer

    if (exit_code == -1) { // Check if the argument is a valid integer
      info->status = 2;
      print_error(info, "Illegal number: ");
      _eputs(info->argv[1]);
      _eputchar('\n');
      exit_status = 1; // Return 1 to indicate an error
    } else {
      exit_status = exit_code;
    }
  }

  exit(exit_status);
}

/**
 * my_cd - changes the current directory of the process
 * @info: pointer to a structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always returns 0.
 */
int my_cd(info_t *info)
{
  char *s, *dir, buffer[1024];
  int chdir_ret;

  s = getcwd(buffer, 1024);
  if (!s) {
    _puts("TODO: >>getcwd failure emsg here<<\n");
  }

  if (!info->argv[1]) { // If no arguments provided, change to the home directory
    dir = _getenv(info, "HOME=");
    if (!dir) {
      chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
    } else {
      chdir_ret = chdir(dir);
    }
  } else if (_strcmp(info->argv[1], "-") == 0) { // If argument is "-"
    if (!_getenv(info, "OLDPWD=")) { // If OLDPWD environment variable is not set
      _puts(s);
      _putchar('\n');
      return (1);
    }
    _puts(_getenv(info, "OLDPWD="));
    _putchar('\n');
    chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
  } else { // If argument is a directory path
    chdir_ret = chdir(info->argv[1]);
  }

  if (chdir_ret == -1) { // If chdir fails, print an error message
    print_error(info, "can't cd to ");
    _eputs(info->argv[1]);
    _eputchar('\n');
  } else { // If chdir succeeds, update the PWD and OLDPWD environment variables
    _setenv(info, "OLDPWD", _getenv(info, "PWD="));
    _setenv(info, "PWD", getcwd(buffer, 1024));
  }

  return (0);
}

/**
 * myhelp - displays help information for shell built-in commands
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myhelp(info_t *info)
{
        char **arg_array;
        int i;

        arg_array = info->argv;
        if (!arg_array[1])
        {
                /* No arguments provided, display general help */
                _puts("Type 'help name' to find out more about the function 'name'.\n");
                _puts("List of built-in commands:\n");
                for (i = 0; i < info->builtin_count; i++)
                {
                        _puts(info->builtin_str[i]);
                        _putchar('\n');
                }
        }
        else
        {
                /* Check if argument is a built-in command and display help if it is */
                for (i = 0; i < info->builtin_count; i++)
                {
                        if (_strcmp(info->argv[1], info->builtin_str[i]) == 0)
                        {
                                _puts(info->builtin_help[i]);
                                _putchar('\n');
                                break;
                        }
                }
                if (i == info->builtin_count)
                {
                        /* Argument not recognized as built-in command */
                        print_error(info, "help: no help topics match ");
                        _eputs(info->argv[1]), _eputchar('\n');
                }
        }
        return (0);
}

