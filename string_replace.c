#include "shell.h"
/**
 * chain_check - function to check chaining based on last status
 * @info: pointer to code_t struct
 * @buffer: pointer to char buffer
 * @ptr: pointer address
 * @n: start position
 * @length: length of buffer
 *
 * Return: void
 */
void chain_check(code_t *info, char *buffer,
		size_t *ptr, size_t n, size_t length)
{
	size_t i = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[n] = 0;
			i = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[n] = 0;
			i = length;
		}
	}

	*ptr = i;
}

/**
 * string_replace - function to replace a string
 * @old: pointer to pointer address of old string
 * @neew: pointer of new string
 *
 * Return: 1 replaced
 */
int string_replace(char **old, char *neew)
{
	free(*old);
	*old = neew;
	return (1);
}

/**
 * variable_replace - function to replace variable
 * @info: pointer to the code_t struct
 *
 * Return: 1 replaced
 */
int variable_replace(code_t *info)
{
	int n = 0;
	node_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!custom_strcmp(info->argv[n], "$?"))
		{
			string_replace(&(info->argv[n]),
					custom_strdup(convert_to_number(info->status, 10, 0)));
			continue;
		}
		if (!custom_strcmp(info->argv[n], "$$"))
		{
			string_replace(&(info->argv[n]),
					custom_strdup(convert_to_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begin_with_prefix(info->env, &info->argv[n][1], '=');
		if (node)
		{
			string_replace(&(info->argv[n]),
					custom_strdup(custom_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&info->argv[n], custom_strdup(""));

	}
	return (0);
}

/**
 * alias_replace - function to replace an alias
 * @info: pointer to the code_t struct
 *
 * Return: 1 replaced
 */
int alias_replace(code_t *info)
{
	int n;
	node_t *node;
	char *s;

	for (n = 0; n < 10; n++)
	{
		node = node_begin_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		s = custom_strchr(node->str, '=');
		if (!s)
			return (0);
		s = custom_strdup(s + 1);
		if (!s)
			return (0);
		info->argv[0] = s;
	}
	return (1);
}

/**
 * chain_test - function test for a chain delimeter
 * @info: pointer to code_t struct
 * @buffer: buffer
 * @ptr: pointer to address
 *
 * Return: 1 chain delimeter
 */
int chain_test(code_t *info, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}
