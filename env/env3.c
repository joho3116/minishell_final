#include "../includes/minishell.h"

char	**get_env_list_with_quotation(void)
{
	char	**ret;
	int		i;
	t_list	*idx;

	ret = (char **)malloc(sizeof(char *) * (count_env_num_all() + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	idx = g_info.env;
	while (idx)
	{
		if (((t_env_node *)(idx->data))->value != NULL)
			ret[i] = unite_key_value_with_quotation(idx);
		else
			ret[i] = ft_strdup(((t_env_node *)(idx->data))->key);
		if (ret[i] == NULL)
		{
			free_envp_list(ret);
			return (NULL);
		}
		++i;
		idx = idx->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	count_env_num_all(void)
{
	int		i;
	t_list	*idx;

	i = 0;
	idx = g_info.env;
	while (idx)
	{
		++i;
		idx = idx->next;
	}
	return (i);
}

int	count_env_num_exclude_null_value(void)
{
	int		i;
	t_list	*idx;

	i = 0;
	idx = g_info.env;
	while (idx)
	{
		if (((t_env_node *)(idx->data))->value != NULL)
			++i;
		idx = idx->next;
	}
	return (i);
}

char	*unite_key_value(t_list *idx)
{
	int		len;
	char	*ret;
	int		i_all;
	int		i_indiv;

	len = ft_strlen(((t_env_node *)(idx->data))->key)
		+ ft_strlen(((t_env_node *)(idx->data))->value) + 1;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i_all = 0;
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->key)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->key)[i_indiv++];
	ret[i_all++] = '=';
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->value)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->value)[i_indiv++];
	ret[i_all] = '\0';
	return (ret);
}

char	*unite_key_value_with_quotation(t_list *idx)
{
	int		len;
	char	*ret;
	int		i_all;
	int		i_indiv;

	len = ft_strlen(((t_env_node *)(idx->data))->key)
		+ ft_strlen(((t_env_node *)(idx->data))->value) + 1 + 2;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i_all = 0;
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->key)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->key)[i_indiv++];
	ret[i_all++] = '=';
	ret[i_all++] = '\"';
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->value)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->value)[i_indiv++];
	ret[i_all++] = '\"';
	ret[i_all] = '\0';
	return (ret);
}
