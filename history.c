#include "kc_shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *get_history_file(info_t *info)
{
    char *dir = getenv("HOME");
    if (!dir)
        return NULL;
    char *buf = malloc(strlen(dir) + strlen(HIST_FILE) + 2);
    if (!buf)
        return NULL;
    sprintf(buf, "%s/%s", dir, HIST_FILE);
    return buf;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;
    FILE *file = fopen(filename, "w");
    free(filename);
    if (!file)
        return -1;
    list_t *node = info->history;
    while (node)
    {
        fprintf(file, "%s\n", node->str);
        node = node->next;
    }
    fflush(file);
    fclose(file);
    return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;
    FILE *file = fopen(filename, "r");
    free(filename);
    if (!file)
        return 0;
    int linecount = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        size_t linelen = strlen(line);
        if (line[linelen - 1] == '\n')
            line[linelen - 1] = '\0';
        build_history_list(info, line, linecount++);
    }
    free(line);
    fclose(file);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);
    renumber_history(info);
    return info->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return 0;
    new_node->str = strdup(buf);
    new_node->index = linecount;
    new_node->next = NULL;
    if (!info->history)
    {
        info->history = new_node;
    }
    else
    {
        list_t *node = info->history;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    return 0;
}

/**
 * update_history - updates the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int update_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	return (info->histcount);
}

