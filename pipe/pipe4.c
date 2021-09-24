#include "../includes/minishell.h"

void	pipe_child_sub(int i, int pipe1[2])
{
	int	error_check;

	error_check = check_output_redirection(i, pipe1);
	if (error_check < 0)
	{
		print_error(error_check, g_info.cmds[i][0]);
		exit(1);
	}
	try_builtin_or_execve(i);
}

void	pipe_parent(int stat_pid_i[3], int pipes[2][2], int *child_stat)
{
	if (stat_pid_i[2] != 0)
	{
		close(pipes[0][0]);
		close(pipes[0][1]);
	}
	copy_pipe_fd(pipes[0], pipes[1]);
	if (g_info.cmds[stat_pid_i[2] + 1] == NULL)
		waitpid(stat_pid_i[1], &child_stat[stat_pid_i[2]], 0);
	else
		waitpid(stat_pid_i[1], &child_stat[stat_pid_i[2]], WNOHANG);
}

int	restore_stdin_stdout(void)
{
	if (dup2(STDIN_BACKUP_FD, 0) < 0)
	{
		ft_perror("dup2");
		return (STD_FD_RESTORE_FAIL);
	}
	if (dup2(STDOUT_BACKUP_FD, 1) < 0)
	{
		ft_perror("dup2");
		return (STD_FD_RESTORE_FAIL);
	}
	return (0);
}

int	check_input_redirection(int i, int pip[])
{
	t_list	*node;
	t_list	*node_of_redir_list;

	node = find_node_at_idx_in_list(g_info.cmd_redir_lst, i);
	if (node == NULL)
		return (REDIR_INFO_NODE_NOT_FOUND);
	node_of_redir_list = node->data;
	while (node_of_redir_list != NULL)
	{
		if (node_of_redir_list->data == NULL)
			return (REDIR_INFO_NODE_NULL);
		if (((t_redir_lst_nod *)(node_of_redir_list->data))->type
		== IN_REDIR_LIM)
			check_input_redir_heredoc(pip, node_of_redir_list);
		else if (((t_redir_lst_nod *)(node_of_redir_list->data))->type
		== IN_REDIR)
			if (check_input_redir_from_file(pip, node_of_redir_list) < 0)
				return (OPEN_ERROR);
		node_of_redir_list = node_of_redir_list->next;
	}
	return (0);
}

void	check_input_redir_heredoc(int pip[], t_list *node_of_redir_list)
{
	char	*line;

	close(pip[0]);
	if (pip[0] != 0)
		close(0);
	pipe(pip);
	if (pip[0] == 0)
		pip[0] = dup(pip[0]), close(0);
	dup2(STDIN_BACKUP_FD, 0);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(((t_redir_lst_nod *)(node_of_redir_list->data))
			->path, line) == 0)
		{
			free(line);
			break ;
		}
		write(pip[1], line, ft_strlen(line)), write(pip[1], "\n", 1);
		free(line);
	}
	close(pip[1]), dup2(pip[0], 0);
}
