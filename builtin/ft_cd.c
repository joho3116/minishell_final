#include "../includes/minishell.h"

int	change_dir_to_arg(char *dir)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		print_error(MALLOC_ERROR, "cd");
		return (1);
	}
	set_new_value_to_existing_key("OLDPWD", tmp);
	if (chdir(dir) < 0)
	{
		print_error(ERRNO_SET, "cd");
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		print_error(MALLOC_ERROR, "cd");
		return (1);
	}
	set_new_value_to_existing_key("PWD", tmp);
	return (0);
}

int	builtin_cd(int i)
{
	char	*tmp;

	if (g_info.cmds[i][1] == NULL)
	{
		tmp = find_key_and_return_value("HOME");
		if (tmp == NULL)
		{
			print_error(MALLOC_ERROR, "cd");
			return (1);
		}
		return (change_dir_to_arg(tmp));
	}
	else if (g_info.cmds[i][2] == NULL)
	{
		return (change_dir_to_arg(g_info.cmds[i][1]));
	}
	else
	{
		ft_putstr_fd("minisehll: cd: too many arguments\n", 2);
		return (1);
	}
}
