#include "kc_shell.h"

/**
 * rand_int - generates a random integer between min and max
 * @min: minimum value
 * @max: maximum value
 *
 * Return: randomly generated integer
 */
int rand_int(int min, int max)
{
    int num;
    if (max < min)
    {
        int temp = max;
        max = min;
        min = temp;
    }
    srand(time(NULL));
    num = (rand() % (max - min + 1)) + min;
    return num;
}

/**
 * print_list_reverse - prints the contents of a linked list in reverse order
 * @head: a pointer to the head node of the linked list
 *
 * Return: the number of nodes in the linked list
 */
int print_list_reverse(list_t *head)
{
	if (head == NULL)
		return (0);

	int count = print_list_reverse(head->next);
	_printf("%s\n", head->str);
	return (count + 1);
}

/**

get_file_size - get the size of a file

@filename: the name of the file

Return: the size of the file, or -1 on error
*/
long int get_file_size(char *filename)
{
FILE *fp;
long int size;

fp = fopen(filename, "r");
if (!fp)
return -1;

fseek(fp, 0L, SEEK_END);
size = ftell(fp);

fclose(fp);

return size;
}

/**
 * my_unset_alias - removes an alias from the list of aliases
 * @info: parameter struct
 * @alias_name: the name of the alias to remove
 *
 * Return: 0 on success, 1 on error
 */
int my_unset_alias(info_t *info, char *alias_name)
{
    int index = get_node_index(info->alias, node_starts_with(info->alias, alias_name, -1));
    if (index == -1)
        return 1;
    return delete_node_at_index(&(info->alias), index);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	list_t *current = info->history;
	int i = 0;

	while (current)
	{
		printf("%d %s\n", i, (char *) current->content);
		current = current->next;
		i++;
	}

	return (0);
}

