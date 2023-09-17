#include "shell.h"
/**
 * custom_cd - function to change current directory
 * @info: pointer to code_t
 *
 * Return: Always 0
 */
int custom_cd(code_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_set;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = custom_get_environ(info, "HOME=");
		if (!dir)
			chdir_set =
				chdir((dir = custom_get_environ(info, "PWD=")) ? dir : "/");
		else
			chdir_set = chdir(dir);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!custom_get_environ(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(custom_get_environ(info, "OLDPWD=")), _putchar('\n');
		chdir_set =
			chdir((dir = custom_get_environ(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_set = chdir(info->argv[1]);
	if (chdir_set == -1)
	{
		custom_print_error(info, "can't cd to ");
		custom_puts(info->argv[1]), custom_putchar('\n');
	}
	else
	{
		custom_setenv(info, "OLDPWD", custom_get_environ(info, "PWD="));
		custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_history - function to display history list
 * @info: pointer to code_t
 *
 *  Return: Always 0
 */
int custom_history(code_t *info)
{
	list_print(info->history);
	return (0);
}

/**
 * custom_help - funtion that changes current directory
 * @info: pointer to code_t struct
 *
 * Return: Always 0
 */
int custom_help(code_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call\n");
	if (0)
		_puts(*arg_array);
	return (0);
}


/**
 * custom_exit - function to exit
 * @info: pointer to code_t
 * Return: given exit status
 *
 */
int custom_exit(code_t *info)
{

	int code_exit;

	if (info->argv[1])
	{
		code_exit = custom_error_atoi(info->argv[1]);
		if (code_exit == -1)
		{
			info->status = 2;
			custom_print_error(info, "Invalid number: ");
			custom_puts(info->argv[1]);
			custom_putchar('\n');
			return (1);
		}
		info->err_num = custom_error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
