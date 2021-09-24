#include "../includes/minishell.h"

void	free_envp_list(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		free(envp[i]);
	}
	free(envp);
}

char	*find_key_and_return_value(char *key)
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
		return (NULL);
	else
		return (((t_env_node *)(idx->data))->value);
}

t_list	*find_key_and_return_node(char *key)
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
		return (NULL);
	else
		return (idx);
}
