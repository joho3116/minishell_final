#include "../includes/minishell.h"

#include <stdio.h>
int	init_minishell_envp(char *envp[])
{
	int			i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (set_new_key(envp[i]) < 0)
			return (-1);
	}
	return (0);
}

void	malloc_and_strcpy_key_value(char *env, char **key, char **value)
{
	int		key_len;

	key_len = ft_key_len(env);
	*key = ft_strndup(env, key_len);
	if (*key == NULL)
	{
		*value = NULL;
		return ;
	}
	*value = ft_strdup(env + key_len + 1);
	if (*value == NULL)
	{
		free(*key), *key = NULL;
		return ;
	}
	return ;
}

t_env_node	*make_env_node(char **key, char **value)
{
	t_env_node	*ret;

	ret = (t_env_node *)malloc(sizeof(t_env_node));
	if (ret == NULL)
	{
		free(*key), free(*value), *key = NULL;
		*value = NULL;
		return (NULL);
	}
	ret->key = *key;
	ret->value = *value;
	*key = NULL;
	*value = NULL;
	return (ret);
}

int	ft_key_len(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = -1;
	while (str[++i] != '=' && str[i] != '\0')
		;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

char	*duplicate_only_value(char *key_value)
{
	int		len;
	char	*ptr;
	char	*ret;

	len = ft_key_len(key_value);
	ptr = key_value + len + 1;
	ret = ft_strdup(ptr);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
