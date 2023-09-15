#include "shell.h"

/**
 * code_set - function to initialize code_t struct
 * @info: pointer to code_t struct
 * @av: pointer to pointer argument vector
 */
void code_set(code_t *info, char **av)
{
	int n = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = custom_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = custom_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		alias_replace(info);
		variable_replace(info);
	}
}

/**
 * code_clear - function to initialize code_t struct
 * @info: pointer to code_t struct
 */
void code_clear(code_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * code_free - function to free code_t struct fields
 * @info: pointer to code_t struct
 * @all: true if freeing all fields
 */
void code_free(code_t *info, int all)
{
	string_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			node_free_list(&(info->env));
		if (info->history)
			node_free_list(&(info->history));
		if (info->alias)
			node_free_list(&(info->alias));
		string_free(info->environ);
		info->environ = NULL;
		memory_free((void **)info->cmd_buf);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
