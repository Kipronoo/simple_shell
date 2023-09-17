#include "shell.h"
/**
 * list_print - function to print all elements
 * @f: pointer to first node
 *
 * Return: list size
 */
size_t list_print(const node_t *f)
{
	size_t n = 0;

	while (f)
	{
		_puts(convert_to_number(f->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		n++;
	}
	return (n);
}

/**
 * node_index_get - function to get node index
 * @head: pointer to the head
 * @node: pointer to the node
 *
 * Return: -1 otherwise index of node
 */
ssize_t node_index_get(node_t *head, node_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}

/**
 * length_list - function to determine list length
 * @f: pointer to first node
 *
 * Return: list size
 */
size_t length_list(const node_t *f)
{
	size_t n = 0;

	while (f)
	{
		f = f->next;
		n++;
	}
	return (n);
}

/**
 * node_begin_with_prefix - function check node whose string starts with prefix
 * @node: pointer to node_t struct
 * @prefix: pointer string to match
 * @c: next character after prefix to match
 *
 * Return: node or null
 */
node_t *node_begin_with_prefix(node_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starts_check(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * string_list - function to returns an array of strings
 * @head: pointer to first node
 *
 * Return: string array
 */
char **string_list(node_t *head)
{
	node_t *node = head;
	size_t n = length_list(head), m;
	char **strings;
	char *str;

	if (!head || !n)
		return (NULL);
	strings = malloc(sizeof(char *) * (n + 1));
	if (!strings)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(custom_strlen(node->str) + 1);
		if (!str)
		{
			for (m = 0; m < n; m++)
				free(strings[m]);
			free(strings);
			return (NULL);
		}

		str = custom_strcpy(str, node->str);
		strings[n] = str;
	}
	strings[n] = NULL;
	return (strings);
}
