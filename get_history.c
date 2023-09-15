#include "shell.h"

/**
 * get_history - function to get the history file
 * @info: pointer to code_t struct
 *
 * Return: buffer
 */

char *get_history(code_t *info)
{
	char *buffer, *dir;

	dir = custom_get_environ(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (custom_strlen(dir)
			+ custom_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	custom_strcpy(buffer, dir);
	custom_strcat(buffer, "/");
	custom_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * reset_history - function to renumbers the history linked list
 * @info: pointer to code_t struct
 *
 * Return: history_count
 */
int reset_history(code_t *info)
{
	node_t *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}

/**
 * history - function to read history from file
 * @info: pointer to code_t struct
 *
 * Return: histcount on success, 0 otherwise
 */
int history(code_t *info)
{
	int n, last = 0, count_line = 0;
	ssize_t file_descriptor, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(file_descriptor, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (n = 0; n < fsize; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			add_history(info, buffer + last, count_line++);
			last = n + 1;
		}
	if (last != n)
		add_history(info, buffer + last, count_line++);
	free(buffer);
	info->histcount = count_line;
	while (info->histcount-- >= HIST_MAX)
		node_index_delete(&(info->history), 0);
	reset_history(info);
	return (info->histcount);
}

/**
 * add_history - function to add to a history linked list
 * @info: pointer to code_t struct
 * @buffer: buffer
 * @count: history count
 *
 * Return: Always 0
 */
int add_history(code_t *info, char *buffer, int count)
{
	node_t *node = NULL;

	if (info->history)
		node = info->history;
	create_node_end(&node, buffer, count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * create_history - function to create a file
 * @info: pointer to code_t struct
 *
 * Return: 1 on success, otherwise -1
 */
int create_history(code_t *info)
{
	ssize_t fd; /* fd file descriptor */
	char *filename = get_history(info);
	node_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		custom_puts_fd(node->str, fd);
		custom_put_fd('\n', fd);
	}
	custom_put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
