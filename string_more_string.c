#include "shell.h"

/**
 * starts_check - checks if needle starts with haystack
 * @haystack: pointer to char
 * @needle: pointer to the substring
 *
 * Return: address or NULL
 */
char *starts_check(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * custom_strlen - function to return string length
 * @str: pointer to char
 *
 * Return: length
 */
int custom_strlen(char *str)
{
	int n = 0;

	if (!str)
		return (0);

	while (*str++)
		n++;
	return (n);
}

/**
 * custom_strcat - function to concatenate two strings
 * @dest: pointer to char
 * @src: pointer to char source
 *
 * Return: destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (str);
}

/**
 * custom_strcmp - function to compare two strangs.
 * @str1: pointer to char
 * @str2: pointer to char
 *
 * Return: negative (s1 < s2), positive (s1 > s2), zero (s1 == s2)
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
