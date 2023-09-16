#include "shell.h"
/**
 * custom_cd - function to change current directory
 * @info: pointer to code_t
 * 
 * Return: Always 0
 */
int custom_cd(code_t *info) {
    char *target_dir;
    char *oldpwd;
    char buffer[1024];

    target_dir = info->argv[1];
    oldpwd = custom_get_environ(info, "PWD");

    if (!target_dir) {
        target_dir = custom_get_environ(info, "HOME");
        if (!target_dir) {
            target_dir = "/";
        }
    } else if (custom_strcmp(target_dir, "-") == 0) {
        if (!oldpwd) {
            printf("%s\n", "TODO: >>getcwd failure emsg here<<");
            return 1;
        }
        target_dir = oldpwd;
    }

    if (chdir(target_dir) == -1) {
        printf("can't cd to %s\n", target_dir);
        return 1;
    }

    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        printf("TODO: >>getcwd failure emsg here<<\n");
        return 1;
    }

    custom_setenv(info, "OLDPWD", oldpwd ? oldpwd : "");
    custom_setenv(info, "PWD", buffer);
    return 0;
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
	_puts("help call works. Function not yet implemented \n");
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
    if (info->argv[1])
    {
        int code_exit = custom_error_atoi(info->argv[1]);
        if (code_exit == -1)
        {
            info->status = 2;
            fprintf(stderr, "invalid: %s\n", info->argv[1]);
            return 1;
        }
        info->err_num = code_exit;
    }
    else
    {
        info->err_num = -1;
    }
    
    return (-2);
}
