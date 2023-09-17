#include "shell.h"
/**
 * fork_command - function fork to run command
 * @info: pointer to code_t struct
 *
 * Return: void
 */
void fork_command(code_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, custom_environ_get(info)) == -1)
		{
			code_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				custom_print_error(info, "Permission denied\n");
		}
	}
}

/**
 * command_path - function to find a command in path
 * @info: pointer to code_t struct
 *
 * Return: void
 */
void command_path(code_t *info)
{
	char *path = NULL;
	int n, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (n = 0, j = 0; info->arg[n]; n++)
		if (!delimiter_check(info->arg[n], " \t\n"))
			j++;
	if (!j)
		return;

	path = path_search(info, custom_get_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((check_interactive(info) || custom_get_environ(info, "PATH=")
					|| info->argv[0][0] == '/') && command_exec(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			custom_print_error(info, "not found\n");
		}
	}
}

/**
 * hsh - main shell loop
 * @info: pointer to the code_t struct
 * @av: argument vector
 *
 * Return: 0 on success otherwise 1
 */
int hsh(code_t *info, char **av)
{
	ssize_t i = 0;
	int command_return = 0;

	while (i != -1 && command_return != -2)
	{
		code_clear(info);
		if (check_interactive(info))
			_puts("$ ");
		custom_putchar(BUF_FLUSH);
		i = get_line(info);
		if (i != -1)
		{
			code_set(info, av);
			command_return = command_find(info);
			if (command_return == -1)
				command_path(info);
		}
		else if (check_interactive(info))
			_putchar('\n');
		code_free(info, 0);
	}
	create_history(info);
	code_free(info, 1);
	if (!check_interactive(info) && info->status)
		exit(info->status);
	if (command_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (command_return);
}
