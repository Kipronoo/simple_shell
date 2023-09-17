#include "shell.h"
/**
 * custom_environ - environ linked list
 * @info: pointer to code_t
 *
 * Return: Always 0
 */
int custom_environ(code_t *info)
{
	node_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		create_node_end(&node, environ[n], 0);
	info->env = node;
	return (0);
}

/**
 * custom_get_environ - obtain value of environ variable
 * @info: pointer to code_t struct
 * @name: pointer to variable name
 *
 * Return: value of the environ
 */
char *custom_get_environ(code_t *info, const char *name)
{
	node_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_check(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * custom_print_environ - print current environ
 * @info: pointer to code_t struct
 *
 * Return: Always 0
 */
int custom_print_environ(code_t *info)
{
	liststr_print(info->env);
	return (0);
}

/**
 * custom_environ_get - function to return the string array
 * @info: pointer to the code_t struct
 *
 * Return: Always 0
 */
char **custom_environ_get(code_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = string_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
