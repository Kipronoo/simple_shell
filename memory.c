#include "shell.h"

/**
 * custom_memset - function to fill memory with a block
 * @s: pointer to the memory area
 * @b: byte to fill
 * @n: amount of bytes to fill
 * Return: s
 */
char *custom_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * string_free - function to free a string
 * @ptr: pointer to pointer string
 */
void string_free(char **ptr)
{
	char **a = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(a);
}

/**
 * memory_free - function to free a pointer
 * @ptr: pointer address to free
 *
 * Return: 1 (freed), 0 (failed)
 */
int memory_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * custom_realloc - function to reallocate memory block
 * @ptr: pointer to memory block
 * @o_size: old size of memory block
 * @n_size: new size of memory block
 *
 * Return: pointer to the new size of memory block.
 */
void *custom_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (p);
}
