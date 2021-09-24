#include "../includes/minishell.h"

int	run_cmd(void)
{
	if (g_info.cmds[1] == NULL)
	{
		return (run_only_one_cmd(0));
	}
	else
	{
		return (run_pipe());
	}
	return (0);
}

int	is_builtin(char *str)
{
	return (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"));
}

int	run_only_one_cmd(int i)
{
	if (is_builtin(g_info.cmds[i][0]))
		return (run_only_one_cmd_builtin(i));
	else
		return (run_pipe());
}

int	run_only_one_cmd_builtin(int i)
{
	int	not_pipe[2];
	int	error_check;
	int	ret;

	not_pipe[0] = 0;
	not_pipe[1] = 1;
	error_check = check_input_redirection(i, not_pipe);
	if (error_check < 0)
		return (run_only_one_cmd_builtin_error_return(i, error_check));
	error_check = check_output_redirection(i, not_pipe);
	if (error_check < 0)
		return (run_only_one_cmd_builtin_error_return(i, error_check));
	ret = builtin_sort(i);
	error_check = restore_stdin_stdout();
	if (error_check < 0)
		return (run_only_one_cmd_builtin_error_return(i, error_check));
	return (ret);
}

int	run_only_one_cmd_builtin_error_return(int i, int error_check)
{
	error_check = restore_stdin_stdout();
	print_error(error_check, g_info.cmds[i][0]);
	return (error_check);
}
