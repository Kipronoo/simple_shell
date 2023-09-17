#include "shell.h"

/**
 * custom_put_fd - writes the character c to given fd
 * @c: character to print
 * @fd: file descriptor
 * Return: 1 success otherwise -1
 *
 */
int custom_put_fd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * custom_puts_fd - function to print input string
 * @str: pointer to char
 * @fd: filedescriptor to write to
 *
 * Return: number of char
 */
int custom_puts_fd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += custom_put_fd(*str++, fd);
	}
	return (n);
}

/**
 * custom_putchar - function to write to standard ouput
 * @c: character to output
 * Return: 1 success
 *
 */
int custom_putchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * custom_error_atoi - function to convert a string to integer
 * @str: string to convert
 * Return: 0 if no numbers in string otherwise -1
 *
 */
int custom_error_atoi(char *str)
{
	int n = 0;
	unsigned long int value = 0;

	if (*str == '+')
		str++;
	for (n = 0;  str[n] != '\0'; n++)
	{
		if (str[n] >= '0' && str[n] <= '9')
		{
			value *= 10;
			value += (str[n] - '0');
			if (value > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (value);
}
