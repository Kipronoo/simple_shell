#include "shell.h"

/**
 * command_exec - function to determine a file is executable command
 * @info: pointer to the code_t struct
 * @path: file path
 *
 * Return: 1 if true, 0 otherwise
 */
int command_exec(code_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * character_duplicate - function to duplicate characters
 * @strpath: pointer to the string path
 * @begin: index to begin
 * @stop: index to stop
 *
 * Return: buffer
 */
char *character_duplicate(char *strpath, int begin, int stop)
{
	static char buffer[1024];
	int n = 0, m = 0;

	for (m = 0, n = begin; n < stop; n++)
		if (strpath[n] != ':')
			buffer[m++] = strpath[n];
	buffer[m] = 0;
	return (buffer);
}

/**
 * path_search - function to find the string path
 * @info: pointer to the code_t struct
 * @strpath: the string path
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_search(code_t *info, char *strpath, char *cmd)
{
	int n = 0, position = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((custom_strlen(cmd) > 2) && starts_check(cmd, "./"))
	{
		if (command_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[n] || strpath[n] == ':')
		{
			path = character_duplicate(strpath, position, n);
			if (!*path)
				custom_strcat(path, cmd);
			else
			{
				custom_strcat(path, "/");
				custom_strcat(path, cmd);
			}
			if (command_exec(info, path))
				return (path);
			if (!strpath[n])
				break;
			position = n;
		}
		n++;
	}
	return (NULL);
}

/**
 * command_find - function to find a command
 * @info: pointer to code_t struct
 *
 * Return: 0 execute successfully,
 * 	1 fail to executed,
 * 	2 command signal exited,
 *     -1 command not found
 */
int command_find(code_t *info)
{
	int n, command_return = -1;
	command_list new_command[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_set_environ},
		{"unsetenv", custom_unset_environ},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (n = 0; new_command[n].type; n++)
		if (custom_strcmp(info->argv[0], new_command[n].type) == 0)
		{
			info->line_count++;
			command_return = new_command[n].func(info);
			break;
		}
	return (command_return);
}
