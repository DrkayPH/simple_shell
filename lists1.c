#include "kc_shell.h"

/**
 * my_list_len - determines length of linked list
 * @head: pointer to the first node of the list
 *
 * Return: size of list
 */
size_t my_list_len(const struct node *head)
{
    size_t count = 0;
    const struct node *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	/* allocate memory for the array of strings */
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	/* loop through the linked list and copy the strings to the array */
	for (i = 0; node; node = node->next, i++)
	{
		str = (char *)malloc(strlen(node->str) + 1);
		if (!str)
		{
			/* free the previously allocated memory if an error occurs */
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		/* copy the string */
		strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		/* print the node's number, if it has one */
		if (h->num != 0) {
			_puts(convert_number(h->num, 10, 0));
			_putchar(':');
			_putchar(' ');
		}

		/* print the node's string, or "(nil)" if it's NULL */
		if (h->str != NULL)
			_puts(h->str);
		else
			_puts("(nil)");

		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		/* check if the node's string starts with the prefix */
		p = starts_with(node->str, prefix);

		/* check if the prefix match and the next character match, if provided */
		if (p && ((c == -1) || (*(p + strlen(prefix)) == c)))
			return (node);

		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index_kc - gets the index of a node in a linked list
 * @head: pointer to the head of the linked list
 * @node: pointer to the node
 *
 * Returns: the index of the node, or -1 if the node is not found
 */
int get_node_index_kc(list_t *head, list_t *node)
{
    int index = 0;

    while (head != NULL) {
        if (head == node) {
            return index;
        }
        head = head->next;
        index++;
    }

    return -1;
}

