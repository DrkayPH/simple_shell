#include "kc_shell.h"

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    if (!old || !new)
        return 0;

    free(*old);
    *old = new;
    return 1;
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			char *num_str = convert_number(info->status, 10, 0);
			if (!num_str)
				return (1);
			if (!replace_string(&(info->argv[i]), _strdup(num_str)))
			{
				free(num_str);
				return (1);
			}
			free(num_str);
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			char *pid_str = convert_number(getpid(), 10, 0);
			if (!pid_str)
				return (1);
			if (!replace_string(&(info->argv[i]), _strdup(pid_str)))
			{
				free(pid_str);
				return (1);
			}
			free(pid_str);
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			char *val = _strchr(node->str, '=') + 1;
			if (!val)
				return (1);
			if (!replace_string(&(info->argv[i]), _strdup(val)))
				return (1);
			continue;
		}
		if (!replace_string(&info->argv[i], _strdup("")))
			return (1);
	}
	return (0);
}

/* Declaration for node_starts_with function */
list_t *node_starts_with(list_t *head, const char *str, char c);

/* Declaration for convert_number function */
char *convert_number(int num, int base, int is_uppercase);

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        free(info->argv[0]);

        p = strchr(node->str, '=');
        if (!p)
            return 0;

        p++;
        info->argv[0] = strdup(p);
        if (!info->argv[0])
            return 0;
    }

    return 1;
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: pointer to current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = '\0';
		j = len;
	}
	
	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = '\0';
		j = len;
	}

	*p = j;
}

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	
	*p = j;
	return (1);
}

