#include "../includes/minishell.h"

int	builtin_exit(int i)
{
	++i;
	exit(g_info.exit_status);
	return (0);
}
