#include "../includes/minishell.h"

int	check_input_redir_from_file(int pip[], t_list *node_of_redir_list)
{
	close(pip[0]);
	if (pip[0] != 0)
		close(0);
	pip[0] = open(((t_redir_lst_nod *)(node_of_redir_list->data))
			->path, O_RDONLY);
	if (pip[0] < 0)
	{
		return (OPEN_ERROR);
	}
	dup2(pip[0], 0);
	return (0);
}

int	check_output_redirection(int i, int pip[])
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
		== OUT_REDIR_APP || ((t_redir_lst_nod *)(node_of_redir_list->data))
			->type == OUT_REDIR)
		{
			if (check_output_redirection_sub(pip, node_of_redir_list) < 0)
				return (OPEN_ERROR);
		}
		node_of_redir_list = node_of_redir_list->next;
	}
	return (0);
}

int	check_output_redirection_sub(int pip[], t_list *node_of_redir_list)
{
	close(pip[1]);
	if (pip[1] != 1)
		close(1);
	if (((t_redir_lst_nod *)(node_of_redir_list->data))->type
	== OUT_REDIR_APP)
		pip[1] = open(((t_redir_lst_nod *)(node_of_redir_list->data))
				->path, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		pip[1] = open(((t_redir_lst_nod *)(node_of_redir_list->data))
				->path, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pip[1] < 0)
	{
		return (OPEN_ERROR);
	}
	dup2(pip[1], 1);
	return (0);
}
