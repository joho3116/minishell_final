#include "../includes/minishell.h"

int	run_pipe(void)
{
	extern const char *const	sys_siglist[];
	int							pipes[2][2];
	int							stat_pid_i[3];
	int							*child_stat;

	child_stat = (int *)malloc(sizeof(int) * num_of_cmd());
	if (child_stat == NULL)
	{
		ft_perror("pipe");
		return (1);
	}
	run_pipe_init(pipes, stat_pid_i);
	while (g_info.cmds[++(stat_pid_i[2])] != NULL)
	{
		if (run_pipe_loop(stat_pid_i, pipes, child_stat) < 0)
			return (1);
	}
	return (run_pipe_return(stat_pid_i, child_stat, (char **)sys_siglist));
}

int	run_pipe_loop(int stat_pid_i[3], int pipes[2][2], int *child_stat)
{
	pipe(pipes[1]);
	stat_pid_i[1] = fork();
	if (stat_pid_i[1] == 0)
		pipe_child(stat_pid_i[2], pipes[0], pipes[1]);
	else if (stat_pid_i[1] > 0)
		pipe_parent(stat_pid_i, pipes, child_stat);
	else
	{
		ft_perror("fork");
		return (1);
	}
	return (0);
}

int	run_pipe_return(int stat_pid_i[3], int *child_stat, char **sys_siglist)
{
	stat_pid_i[0] = WEXITSTATUS(child_stat[--(stat_pid_i[2])]);
	if (WIFSIGNALED(child_stat[stat_pid_i[2]]))
	{
		stat_pid_i[0] = WTERMSIG(child_stat[stat_pid_i[2]]) + 128;
		if (WTERMSIG(child_stat[stat_pid_i[2]]) != 2)
			print_sig_error((char **)sys_siglist, child_stat, stat_pid_i[2]);
	}
	free(child_stat);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (stat_pid_i[0]);
}

void	print_sig_error(char *sys_siglist[], int *child_stat, int i)
{
	ft_putstr_fd((char *)sys_siglist
	[WTERMSIG(child_stat[i])], 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(WTERMSIG(child_stat[i]), 2);
	ft_putstr_fd("\n", 2);
}

void	pipe_child(int i, int pipe0[2], int pipe1[2])
{
	int	error_check;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i != 0)
	{
		close(pipe0[1]);
		dup2(pipe0[0], 0);
	}
	error_check = check_input_redirection(i, pipe0);
	if (error_check < 0)
	{
		print_error(error_check, g_info.cmds[i][0]);
		exit(1);
	}
	close(pipe1[0]);
	if (g_info.cmds[i + 1] == NULL)
		close(pipe1[1]);
	else
		dup2(pipe1[1], 1);
	pipe_child_sub(i, pipe1);
}
