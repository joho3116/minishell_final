#include "../includes/minishell.h"

int	set_new_value_to_existing_key(char *key, char *new_value)
{
	t_list	*idx;

	idx = g_info.env;
	while (idx)
	{
		if (ft_strcmp(key, ((t_env_node *)(idx->data))->key) == 0)
			break ;
		idx = idx->next;
	}
	if (idx == NULL)
		return (-1);
	if (((t_env_node *)(idx->data))->value != NULL)
		free(((t_env_node *)(idx->data))->value);
	((t_env_node *)(idx->data))->value = new_value;
	return (0);
}

void	find_key_and_unset(char *key)
{
	t_list	*idx;
	t_list	*before_idx;

	before_idx = NULL;
	idx = g_info.env;
	while (idx)
	{
		if (ft_strcmp(key, ((t_env_node *)(idx->data))->key) == 0)
			break ;
		before_idx = idx;
		idx = idx->next;
	}
	if (idx == NULL)
		return ;
	if (before_idx == NULL)
		g_info.env = idx->next;
	else
		before_idx->next = idx->next;
	free(((t_env_node *)(idx->data))->key);
	if (((t_env_node *)(idx->data))->value != NULL)
		free(((t_env_node *)(idx->data))->value);
	free(idx->data);
	free(idx);
}

int	set_new_key(char *key_and_value)
{
	char		*key_tmp;
	char		*value_tmp;
	t_env_node	*data;
	t_list		*node;

	malloc_and_strcpy_key_value(key_and_value, &key_tmp, &value_tmp);
	if (key_tmp == NULL || value_tmp == NULL)
		return (set_new_key_malloc_error_return());
	data = make_env_node(&key_tmp, &value_tmp);
	if (data == NULL)
		return (set_new_key_malloc_error_return());
	node = ft_lstnew((void *)data);
	if (node == NULL)
	{
		free(data->key);
		free(data->value);
		free(data);
		return (set_new_key_malloc_error_return());
	}
	ft_lstadd_back(&(g_info.env), node);
	return (0);
}

int	set_new_key_malloc_error_return(void)
{
	print_error(MALLOC_ERROR, "set new key");
	return (-1);
}

char	**get_env_list(void)
{
	char	**ret;
	int		i;
	t_list	*idx;

	ret = malloc(sizeof(char *) * (count_env_num_exclude_null_value() + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	idx = g_info.env;
	while (idx)
	{
		if (((t_env_node *)(idx->data))->value != NULL)
		{
			ret[i] = unite_key_value(idx);
			if (ret[i] == NULL)
			{
				free_envp_list(ret);
				return (NULL);
			}
			++i;
		}
		idx = idx->next;
	}
	ret[i] = NULL;
	return (ret);
}
