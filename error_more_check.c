#include "shell.h"

/**
 * print_decimal - function to print a decimal number
 * @input: input number
 * @fd: filedescriptor
 *
 * Return: number of printed characters
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = custom_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * custom_puts - function to output a string
 * @str: string to output
 *
 * Return: Nothing
 */
void custom_puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		custom_putchar(str[n]);
		n++;
	}
}

/**
 * custom_print_error - function to print error message
 * @info: pointer to code_t struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string otherwise -1
 *
 */
void custom_print_error(code_t *info, char *str)
{
	custom_puts(info->fname);
	custom_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(info->argv[0]);
	custom_puts(": ");
	custom_puts(str);
}

/**
 * replace_instance - replaces '#' with '\0'
 * @str: pointer to char
 *
 * Return: Always 0;
 */
void replace_instance(char *str)
{
	int n;

	for (n = 0; str[n] != '\0'; n++)
		if (str[n] == '#' && (!n || str[n - 1] == ' '))
		{
			str[n] = '\0';
			break;
		}
}

/**
 * convert_to_number - function converter
 * @num: number to convert
 * @base: number base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_to_number(long int num, int base, int flags)
{
	static char buffer[BUFFER_SIZE];
	char *array = (flags & CONVERT_LOWERCASE)
		? "0123456789abcdef" : "0123456789ABCDEF";
	char *ptr = &buffer[BUFFER_SIZE - 1];
	*ptr = '\0';

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		num = -num;
		*--ptr = '-';
	}

	do {
		*--ptr = array[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}
