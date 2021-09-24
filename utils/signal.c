#include "../includes/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_on_main_at_run_cmd(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_BACKUP_FD, "\n", 1);
}
