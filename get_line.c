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
	size_t q;
	ssize_t t = 0, j = 0;
	char *p = NULL, *p_new = NULL, *str;

	p = *pt;
	if (p && len)
		j = *len;
	if (n == length)
		n = length = 0;

	t = buffer(info, buf, &length);
	if (t == -1 || (t == 0 && length == 0))
		return (-1);

	str = custom_strchr(buf + n, '\n');
	q = str ? 1 + (unsigned int)(str - buf) : length;
	p_new = custom_realloc(p, j, j ? j + q : q + 1);
	if (!p_new)
		return (p ? free(p), -1 : -1);

	if (j)
		custom_strncat(p_new, buf + n, q - n);
	else
		custom_strncpy(p_new, buf + n, q - n + 1);

	j += q - n;
	n = q;
	p = p_new;

	if (len)
		*len = j;
	*pt = p;
	return (j);
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
		read = custom_getline(info, buffer, &len);
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
			if (custom_strchr(*buffer, ';'))
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
	static char *buffer;
	static size_t n, m, length;
	ssize_t read = 0;
	char **buf = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	read = buffer_command(info, &buffer, &length);
	if (read == -1)
		return (-1);
	if (length)
	{
		m = n;
		ptr = buffer + n;

		chain_check(info, buffer, &m, n, length);
		while (m < length)
		{
			if (chain_test(info, buffer, &m))
				break;
			m++;
		}

		n = m + 1;
		if (n >= length)
		{
			n = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf = ptr;
		return (custom_strlen(ptr));
	}

	*buf = buffer;
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
