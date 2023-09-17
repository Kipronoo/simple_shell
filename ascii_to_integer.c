#include "shell.h"

/**
 * ascii_to_integer - function to convert string to integer
 * @s: pointer to char
 * Return: converted number otherwise 0 
 */
int ascii_to_integer(char *s)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/* Handle leading whitespaces */
	while (s[i] == ' ' || s[i] == '\t')
	{
		i++;
	}

	/* Check for a sign character */
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
	{
		i++;
	}

	/* Convert digits to integer */
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = ((result * 10) + (s[i] - '0'));
		i++;
	}

	return (sign * result);
}


/**
 * is_alphabet - function to check alphabet
 * @c: character
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * delimiter_check - function to check character 
 * @c: character
 * @delimiter: pointer to char
 * Return: 1 true, 0 false
 */
int delimiter_check(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter++ == c)
		{
			return (1);
		}
	}
	return (0);
}


/**
 * check_interactive - defines a function 
 * @info: pointer argument to info_t
 * Return: 1 interactive mode, 0 non interactive
 *
 */
int check_interactive(code_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_file_descriptor <= STDERR_FILENO);
}
