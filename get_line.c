#include "shell.h"
/**
 * buffer - function to read a buffer
 * @info: pointer struct
 * @buffer: buffer
 * @n: size
 *
 * Return: value
 */
ssize_t buffer(code_t *info, char *buffer, size_t *n)
{
	ssize_t value = 0;

	if (*n)
		return (0);
	value = read(info->read_file_descriptor, buffer, READ_BUF_SIZE);
	if (value >= 0)
		*n = value;
	return (value);
}

/**
 * custom_getline - function to get the next line input
 * @info: pointer to code_t struct
 * @pt: pointe to pointer to char
 * @len: pointer to size_t of buffer
 *
 * Return: s
 */
int custom_getline(code_t *info, char **pt, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t n, length;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *p_new = NULL, *c;

	p = *pt;
	if (p && len)
		s = *len;
	if (n == length)
		n = length = 0;

	r = buffer(info, buf, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = custom_strchr(buf + n, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : length;
	p_new = custom_realloc(p, s, s ? s + k : k + 1);
	if (!p_new)
		return (p ? free(p), -1 : -1);

	if (s)
		custom_strncat(p_new, buf + n, k - n);
	else
		custom_strncpy(p_new, buf + n, k - n + 1);

	s += k - n;
	n = k;
	p = p_new;

	if (len)
		*len = s;
	*pt = p;
	return (s);
}

/**
 * buffer_command - function buffer chained commands
 * @info: pointer on code_t struct
 * @buffer: pointer to pointer address of buffer
 * @length: variable address
 *
 * Return: read
 */
ssize_t buffer_command(code_t *info, char **buffer, size_t *length)
{
	ssize_t read = 0;
	size_t len = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = getline(buffer, &len, stdin);
#else
		read = custom_getline(info, buffer, &len);
#endif
		if (read > 0)
		{
			if ((*buffer)[read - 1] == '\n')
			{
				(*buffer)[read - 1] = '\0';
				read--;
			}
			info->linecount_flag = 1;
			replace_instance(*buffer);
			add_history(info, *buffer, info->histcount++);
			{
				*length = read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (read);
}

/**
 * get_line - function to get a line
 * @info: pointer to code_t struct
 *
 * Return: read
 */
ssize_t get_line(code_t *info)
{
	static char *buf;
	static size_t i, j, length;
	ssize_t read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read = buffer_command(info, &buf, &length);
	if (read == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buf + i;

		chain_check(info, buf, &j, i, length);
		while (j < length)
		{
			if (chain_test(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (custom_strlen(p));
	}

	*buf_p = buf;
	return (read);
}

/**
 * sigintHandler - ctrl-C block
 * @signal_number: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
