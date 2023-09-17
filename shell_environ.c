#include "shell.h"
/**
 * custom_setenv - set new or modify environ variable
 * @info: pointer to code_t
 * @var: pointer to environ variable
 * @value: pointer to environ value
 * Return: Always 0
 *
 */
int custom_setenv(code_t *info, char *var, char *value)
{
	char *buffer = NULL;
	node_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(custom_strlen(var) + custom_strlen(value) + 2);
	if (!buffer)
		return (1);
	custom_strcpy(buffer, var);
	custom_strcat(buffer, "=");
	custom_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		ptr = starts_check(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	create_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * custom_unsetenv - Remove environ variable
 * @info: pointer to code_t struct
 * Return: 1 on delete, otherwise 0
 * @var: pointer to environ property
 *
 */
int custom_unsetenv(code_t *info, char *var)
{
	node_t *node = info->env;
	size_t n = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_check(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = node_index_delete(&(info->env), n);
			n = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (info->env_changed);
}

/**
 * custom_set_environ - set new environ variable
 * @info: pointer to the code_t struct
 *  Return: Always 0
 *
 */
int custom_set_environ(code_t *info)
{
	if (info->argc != 3)
	{
		custom_puts("Invalid arguement number\n");
		return (1);
	}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * custom_unset_environ - Remove an environ variable
 * @info: pointer to code_t struct
 * 
 * Return: Always 0
 */
int custom_unset_environ(code_t *info)
{
	int n;

	if (info->argc == 1)
	{
		custom_puts("few arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		custom_unsetenv(info, info->argv[n]);

	return (0);
}
