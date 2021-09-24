#include "../includes/minishell.h"

int	builtin_env(int i)
{
	t_list		*idx;
	t_env_node	*env_data;

	if (g_info.cmds[i][1] != NULL)
	{
		print_error(ENV_ARG_ERROR, "env");
		return (1);
	}
	idx = g_info.env;
	while (idx)
	{
		env_data = idx->data;
		if (env_data->value != NULL)
		{
			ft_putstr_fd(env_data->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_data->value, 1);
			ft_putchar_fd('\n', 1);
		}
		idx = idx->next;
	}
	return (0);
}
