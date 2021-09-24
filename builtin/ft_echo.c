#include "../includes/minishell.h"

int	builtin_echo(int i)
{
	bool	flag_new_line;
	int		idx;

	flag_new_line = true;
	idx = 0;
	if (g_info.cmds[i][1] != NULL && ft_strcmp(g_info.cmds[i][1], "-n") == 0)
	{
		flag_new_line = false;
		while (ft_strcmp(g_info.cmds[i][idx + 1], "-n") == 0)
			++idx;
	}
	while (g_info.cmds[i][++idx] != NULL)
	{
		ft_putstr_fd(g_info.cmds[i][idx], 1);
		if (g_info.cmds[i][idx + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (flag_new_line == true)
		ft_putstr_fd("\n", 1);
	return (0);
}
