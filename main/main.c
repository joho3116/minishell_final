#include "../includes/minishell.h"
#include <stdio.h>

t_info	g_info;

bool	is_only_white_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		++line;
	}
	return (true);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		error_check;
	char	*prompt;

	++argc, ++argv;
	dup2(0, STDIN_BACKUP_FD);
	dup2(1, STDOUT_BACKUP_FD);
	error_check = init_minishell_envp(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (error_check < 0)
	{
		print_error(error_check, "init minishell");
		exit(1);
	}
	if (isatty(0) == 1 || isatty(1) == 1)
		prompt = "$> ";
	else
		prompt = "";
	while (1)
	{
		loop_sub(prompt);
	}
}

void	loop_sub(char *prompt)
{
	char	*line;
	int		error_check;

	line = readline(prompt);
	if (line == NULL)
		write(1, "exit\n", 5), exit(g_info.exit_status);
	if (is_only_white_spaces(line))
	{
		free(line);
		return ;
	}
	add_history(line);
	error_check = tokenize(line);
	if (error_check < 0)
	{
		ft_lstclear(&(g_info.lex_head), &free), free(line);
		return ;
	}
	parse_and_run(line);
}

void	parse_and_run(char *line)
{
	int	error_check;

	error_check = parse_all();
	if (error_check < 0)
	{
		free_parse_malloc_in_global_var(), free(line);
		if (error_check == SYNTAX_ERROR)
			print_error(SYNTAX_ERROR, ""), g_info.exit_status = 2;
		return ;
	}
	error_check = run_cmd();
	g_info.exit_status = error_check, free_parse_malloc_in_global_var();
	free(line);
}
