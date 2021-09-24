#include "../includes/minishell.h"

int	builtin_sort(int i)
{
	if (ft_strcmp(g_info.cmds[i][0], "echo") == 0)
		return (builtin_echo(i));
	else if (ft_strcmp(g_info.cmds[i][0], "cd") == 0)
		return (builtin_cd(i));
	else if (ft_strcmp(g_info.cmds[i][0], "pwd") == 0)
		return (builtin_pwd(i));
	else if (ft_strcmp(g_info.cmds[i][0], "export") == 0)
		return (builtin_export(i));
	else if (ft_strcmp(g_info.cmds[i][0], "unset") == 0)
		return (builtin_unset(i));
	else if (ft_strcmp(g_info.cmds[i][0], "env") == 0)
		return (builtin_env(i));
	else if (ft_strcmp(g_info.cmds[i][0], "exit") == 0)
		return (builtin_exit(i));
	return (0);
}

void	copy_pipe_fd(int a[], int b[])
{
	a[0] = b[0];
	a[1] = b[1];
}

int	num_of_cmd(void)
{
	int	cnt;

	cnt = -1;
	while (g_info.cmds[++cnt] != NULL)
		;
	return (cnt);
}

void	run_pipe_init(int pipes[2][2], int stat_pid_i[3])
{
	signal(SIGINT, sig_handler_on_main_at_run_cmd);
	signal(SIGQUIT, sig_handler_on_main_at_run_cmd);
	pipes[0][0] = 0;
	pipes[0][1] = 1;
	stat_pid_i[2] = -1;
}
