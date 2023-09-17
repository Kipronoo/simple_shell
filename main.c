#include "shell.h"
/**
 * main - entry point
 * @ac: argument count
 * @av: pointer to pointer argument vector
 * 
 * Return: 0 on success otherwise 1
 */
int main(int ac, char **av)
{
	code_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	if (ac == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_puts(av[0]);
				custom_puts(": 0: Can't open ");
				custom_puts(av[1]);
				custom_putchar('\n');
				custom_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_descriptor = file_descriptor;
	}
	custom_environ(info);
	history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
