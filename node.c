#include "shell.h"
/**
 * create_node - function to create a node
 * @head: pointer to pointer address
 * @str: string field
 * @num: node index
 *
 * Return: size of list
 */
node_t *create_node(node_t **head, const char *str, int num)
{
	node_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(node_t));
	if (!new_head)
		return (NULL);
	custom_memset((void *)new_head, 0, sizeof(node_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = custom_strdup(str);
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

/**
 * create_node_end - function to create a node to the end of the list
 * @head: pointer to pointer to head node
 * @str: pointer field of node
 * @num: node index
 *
 * Return: size of list
 */
node_t *create_node_end(node_t **head, const char *str, int num)
{
	node_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	custom_memset((void *)new_node, 0, sizeof(node_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = custom_strdup(str);
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
 * node_index_delete - function to delete node at given index
 * @head: pointer to pointer address
 * @index: index of node to delete
 *
 * Return: 1 on success, otherwise 0
 */
int node_index_delete(node_t **head, unsigned int index)
{
	node_t *node, *node_prev;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (n == index)
		{
			node_prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		n++;
		node_prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * node_free_list - function to free all nodes
 * @head_p: pointer to head node
 *
 * Return: void
 */
void node_free_list(node_t **head_p)
{
	node_t *node, *node_next, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		node_next = node->next;
		free(node->str);
		free(node);
		node = node_next;
	}
	*head_p = NULL;
}

/**
 * liststr_print - function to print only the str element
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t liststr_print(const node_t *f)
{
	size_t n = 0;

	while (f)
	{
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		n++;
	}
	return (n);
}
