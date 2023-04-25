#include "kc_shell.h"

/**
 * print_env - prints the current environment
 * @envp: Array of strings containing the environment variables.
 * Return: Always 0
 */
int print_env(char **envp)
{
    char **ptr;

    for (ptr = envp; *ptr != NULL; ptr++)
        printf("%s\n", *ptr);

    return (0);
}

/**
 * my_getenv - gets the value of an environment variable
 * @env: an array of strings containing the environment variables
 * @name: the name of the environment variable to retrieve
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *my_getenv(char **env, const char *name)
{
	char *p;

	while (*env != NULL)
	{
		p = starts_with(*env, name);
		if (p && *p)
			return p;
		env++;
	}
	return NULL;
}

/**
 * mysetenv - Initializes a new environment variable or modifies an existing one
 * @key: the name of the environment variable
 * @value: the value to set for the environment variable
 * @overwrite: flag indicating whether to overwrite an existing value
 *
 * Returns 0 on success or -1 on error.
 */
int mysetenv(const char *key, const char *value, int overwrite) {
    if (key == NULL || value == NULL) {
        return -1;
    }

    size_t key_len = strlen(key);
    size_t value_len = strlen(value);
    char *env_str = (char *) malloc(key_len + value_len + 2);

    if (env_str == NULL) {
        return -1;
    }

    snprintf(env_str, key_len + value_len + 2, "%s=%s", key, value);

    if (overwrite) {
        if (setenv(key, value, 1) == -1) {
            free(env_str);
            return -1;
        }
    } else {
        if (setenv(key, value, 0) == -1 && errno == EINVAL) {
            if (putenv(env_str) != 0) {
                free(env_str);
                return -1;
            }
        }
    }

    free(env_str);
    return 0;
}

/**
 * my_unsetenv - Remove an environment variable
 * @name: Name of the environment variable to remove
 *  Return: Always 0
 */
int my_unsetenv(const char *name)
{
    if (unsetenv(name) != 0) {
        perror("Failed to unset environment variable");
        return 1;
    }

    return 0;
}

/**
 * my_populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i = 0;
    char **envp = NULL;

    // Get the process environment variables
    envp = (char **)environ;

    // Loop through each environment variable and add it to the linked list
    while (envp[i] != NULL) {
        add_node_end(&node, envp[i], 0);
        i++;
    }

    // Set the env field of the info structure to the linked list
    info->env = node;

    return 0;
}

