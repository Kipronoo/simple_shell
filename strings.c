#include "shell.h"
/**
 * custom_strchr - function that locate a character in a string
 * @str: string to be parsed
 * @c: character to look for
 * Return: str
 */
char *custom_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * custom_strncat - concatenate two strings
 * @dest: pointer destination
 * @src: pointer source
 * @n: number
 * Return: concatenated string
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int d, m;
	char *str = dest;

	d = 0;
	m = 0;
	while (dest[d] != '\0')
		n++;
	while (src[m] != '\0' && m < n)
	{
		dest[d] = src[m];
		d++;
		m++;
	}
	if (m < n)
		dest[d] = '\0';
	return (str);
}

/**
 * custom_strncpy - copies a string
 * @dest: pointer destination
 * @src: pointer source
 * @n: character amount copy
 * Return: concatenated string
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int d, m;
	char *str = dest;

	d = 0;
	while (src[d] != '\0' && d < n - 1)
	{
		dest[d] = src[d];
		d++;
	}
	if (d < n)
	{
		m = d;
		while (m < n)
		{
			dest[m] = '\0';
			m++;
		}
	}
	return (str);
}

/**
 * custom_strcpy - copies a string
 * @dest: pointer to the destination
 * @src: pointer to the source
 *
 * Return: pointer to destination
 */
char *custom_strcpy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * custom_strdup - function to duplicate a string
 * @str: pointer to char
 *
 * Return: value
 */
char *custom_strdup(const char *str)
{
	int len = 0;
	char *value;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	for (len++; len--;)
		value[len] = *--str;
	return (value);
}
