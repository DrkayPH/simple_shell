#include "kc_shell.h"

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_reverse - prints the elements of a list_t linked list in reverse order
 * @head: pointer to head node
 *
 * Return: size of list
 */
size_t print_list_reverse(const list_t *head)
{
	size_t i = 0;

	if (head)
	{
		i += print_list_reverse(head->next);
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		i++;
	}
	return (i);
}

/**
 * delete_node_by_value - removes the first occurrence of a node with a given value
 * @head: pointer to pointer to head node
 * @value: value of node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_by_value(list_t **head, const char *value)
{
	list_t *node, *prev_node;

	if (!head || !*head)
		return (0);

	node = *head;
	if (strcmp(node->str, value) == 0)
	{
		*head = node->next;
		free(node->str);
		free(node);
		return (1);
	}

	prev_node = node;
	node = node->next;
	while (node)
	{
		if (strcmp(node->str, value) == 0)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * reverse_list - reverses a singly linked list
 * @head: address of pointer to head node
 *
 * Return: void
 */
void reverse_list(list_t **head)
{
	list_t *prev = NULL;
	list_t *curr = *head;
	list_t *next = NULL;

	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
