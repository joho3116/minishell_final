#include "../includes/minishell.h"

char	**ascending_env_key(t_list *idx, char **ret)
{
	int		idx_size;
	int		i;
	int		step;
	char	**tmps_str;
	char	*tmp_str;

	i = -1;
	tmps_str = ret;
	idx_size = ft_lstsize(idx);
	while (++i < idx_size - 1)
	{
		step = -1;
		while (++step < idx_size - 1 - i)
		{
			if (ft_strcmp(tmps_str[step], tmps_str[step + 1]) > 0)
			{
				tmp_str = tmps_str[step];
				tmps_str[step] = tmps_str[step + 1];
				tmps_str[step + 1] = tmp_str;
			}
		}
	}
	return (tmps_str);
}

int	put_env_list(void)
{
	t_list	*idx;
	char	**ret;
	char	**tmps_str;

	idx = g_info.env;
	ret = get_env_list_with_quotation();
	tmps_str = ret;
	tmps_str = ascending_env_key(idx, ret);
	while (*tmps_str)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(*tmps_str++, 1);
		ft_putchar_fd('\n', 1);
	}
	free_envp_list(ret);
	return (0);
}

int	set_only_key(char *key)
{
	char		*tmp;
	t_env_node	*data;
	t_list		*node;

	tmp = ft_strdup(key);
	data = (t_env_node *)malloc(sizeof(t_env_node));
	if (tmp == NULL || data == NULL)
	{
		print_error(MALLOC_ERROR, "set only key");
		return (-1);
	}
	data->key = tmp;
	data->value = NULL;
	node = ft_lstnew(data);
	if (node == NULL)
	{
		free(data->key);
		free(data);
		print_error(MALLOC_ERROR, "set only key");
		return (-1);
	}
	ft_lstadd_back(&(g_info.env), node);
	return (0);
}

int	builtin_export(int i)
{
	int		j;
	bool	error_flag;

	error_flag = false;
	j = 0;
	if (g_info.cmds[i][1] == NULL)
		put_env_list();
	else
	{
		while (g_info.cmds[i][++j])
		{
			if (ft_strchr(g_info.cmds[i][j], '=') == NULL)
			{
				if (find_key_and_return_value(g_info.cmds[i][j]) == NULL)
					if (set_only_key(g_info.cmds[i][j]) < 0)
						error_flag = true;
			}
			else
				builtin_export_sub(i, j, &error_flag);
		}
	}
	if (error_flag == true)
		return (1);
	return (0);
}

void	builtin_export_sub(int i, int j, bool *error_flag)
{
	char	buf[1024];
	t_list	*tmp;

	ft_strlcpy(buf, g_info.cmds[i][j], 1024);
	buf[ft_key_len(buf)] = '\0';
	if (ft_strlen(buf) == 0)
	{
		*error_flag = true;
		print_error(NOT_A_VALID_IDENTIFIER, "minishell: export");
	}
	else if (find_key_and_return_value(buf) == NULL)
	{
		if (set_new_key(g_info.cmds[i][j]) < 0)
			*error_flag = true;
	}
	else
	{
		tmp = find_key_and_return_node(buf);
		if (((t_env_node *)(tmp->data))->value != NULL)
			free(((t_env_node *)(tmp->data))->value);
		((t_env_node *)(tmp->data))->value
			= duplicate_only_value(g_info.cmds[i][j]);
		if (((t_env_node *)(tmp->data))->value == NULL)
			*error_flag = true;
	}
}
