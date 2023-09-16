#include "shell.h"

/**
 * custom_alias_unset - set alias to string
 * @info: pointer to code_t struct
 * @str: pointer to the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_alias_unset(code_t *info, char *str)
{
	char *ptr, c;
	int pos;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	pos = node_index_delete(&(info->alias),
		node_index_get(info->alias, node_begin_with_prefix(info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * custom_alias_set - set alias
 * @info: pointer to the struct
 * @str: pointer to string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_alias_set(code_t *info, char *str)
{
	char *ptr;

	ptr = custom_strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (custom_alias_unset(info, str));

	custom_alias_unset(info, str);
	return (create_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * custom_alias_print - function to print an alias
 * @node: pointer to the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int custom_alias_print(node_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = custom_strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * custom_alias - mimics the alias (man alias)
 * @info: pointer to the code_t
 *
 *  Return: Always 0
 */
int custom_alias(code_t *info)
{
	int i = 0;
	char *ptr = NULL;
	node_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			custom_alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = custom_strchr(info->argv[i], '=');
		if (ptr)
			custom_alias_set(info, info->argv[i]);
		else
			custom_alias_print(node_begin_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
