#include "shell.h"
/**
 * string_to_word - function to split a string into words
 * @str: pointer to the input string
 * @delimeter: delimeter
 * Return: a pointer or NULL
 */
char **string_to_word(char *str, char delimeter)
{
	int n, i, a, b, word = 0;
	char **v;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != delimeter && str[n + 1] == delimeter) ||
				(str[n] != delimeter && !str[n + 1]) || str[n + 1] == delimeter)
			word++;
	if (word == 0)
		return (NULL);
	v = malloc((1 + word) * sizeof(char *));
	if (!v)
		return (NULL);
	for (n = 0, i = 0; i < word; i++)
	{
		while (str[n] == delimeter && str[n] != delimeter)
			n++;
		a = 0;
		while (str[n + a] != delimeter && str[n + a] && str[n + a] != delimeter)
			a++;
		v[i] = malloc((a + 1) * sizeof(char));
		if (!v[i])
		{
			for (a = 0; a < i; a++)
				free(v[a]);
			free(v);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			v[i][b] = str[n++];
		v[i][b] = 0;
	}
	v[i] = NULL;
	return (v);
}

/**
 * custom_strtow - function to split a string into words
 * @str: pointer to the string
 * @delimeter: delimeter string
 *
 * Return: pointer array or NULL
 */

char **custom_strtow(char *str, char *delimeter)
{
	int n, i, a, b, word = 0;
	char **v;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!delimiter_check(str[n], delimeter) &&
				(delimiter_check(str[n + 1], delimeter) || !str[n + 1]))
			word++;

	if (word == 0)
		return (NULL);
	v = malloc((1 + word) * sizeof(char *));
	if (!v)
		return (NULL);
	for (n = 0, i = 0; i < word; i++)
	{
		while (delimiter_check(str[n], delimeter))
			n++;
		a = 0;
		while (!delimiter_check(str[n + a], delimeter) && str[n + a])
			a++;
		v[i] = malloc((a + 1) * sizeof(char));
		if (!v[i])
		{
			for (a = 0; a < i; a++)
				free(v[a]);
			free(v);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			v[i][b] = str[n++];
		v[i][b] = 0;
	}
	v[i] = NULL;
	return (v);
}
