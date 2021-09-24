#include"../includes/minishell.h"

int	builtin_pwd(int i)
{
	char	*path;

	++i;
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	return (0);
}
