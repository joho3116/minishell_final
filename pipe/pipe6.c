#include "../includes/minishell.h"

int	find_index_of_path_in_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
	}
	return (-1);
}

char	*pipe_strjoin(char *s1, char *s2, char *s3)
{
	int		len;
	char	*ret;
	char	*temp1;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	temp1 = ft_strjoin(s1, s2);
	if (!temp1)
		return (NULL);
	ret = ft_strjoin(temp1, s3);
	free(temp1);
	if (!ret)
		return (NULL);
	len += 1;
	return (ret);
}

void	try_builtin_or_execve(int i)
{
	int		error_check;
	char	**envp;

	if (is_builtin(g_info.cmds[i][0]))
		exit(run_only_one_cmd_builtin(i));
	else
	{
		envp = get_env_list();
		if (envp == NULL)
		{
			ft_perror(g_info.cmds[i][0]);
			exit(1);
		}
		if (g_info.cmds[i][0][0] == '/' || g_info.cmds[i][0][0] == '.')
		{
			execve(g_info.cmds[i][0], g_info.cmds[i], envp);
			ft_putstr_fd("minishell: ", 2);
			ft_perror(g_info.cmds[i][0]);
			exit(127);
		}
		error_check = try_builtin_or_execve_sub(i, envp);
	}
	free_envp_list(envp);
	print_error(error_check, g_info.cmds[i][0]);
	exit(1);
}

int	try_builtin_or_execve_sub(int i, char **envp)
{
	int		path_idx;
	int		path_string_idx;
	char	*tmp;

	path_idx = find_index_of_path_in_env(envp);
	if (path_idx < 0)
		return (CMD_NOT_FOUND);
	path_string_idx = 5;
	while (envp[path_idx][path_string_idx] != '\0')
	{
		tmp = try_builtin_or_execve_sub2(&path_string_idx, path_idx, i, envp);
		if (tmp == NULL)
		{
			return (MALLOC_ERROR);
		}
		execve(tmp, g_info.cmds[i], envp);
		free(tmp);
	}
	return (CMD_NOT_FOUND);
}

char	*try_builtin_or_execve_sub2(int *path_string_idx, int path_idx, int i
, char **envp)
{
	int		end_idx;
	char	*tmp;
	char	*ret;

	end_idx = *path_string_idx;
	while (envp[path_idx][end_idx] != ':' && envp[path_idx][end_idx] != '\0')
		++end_idx;
	tmp = ft_strndup(envp[path_idx] + (*path_string_idx),
			end_idx - *path_string_idx);
	if (tmp == NULL)
		return (NULL);
	ret = pipe_strjoin(tmp, "/", g_info.cmds[i][0]);
	free(tmp);
	if (ret == NULL)
		return (NULL);
	if (envp[path_idx][end_idx] == ':')
		*path_string_idx = end_idx + 1;
	else
		*path_string_idx = end_idx;
	return (ret);
}
