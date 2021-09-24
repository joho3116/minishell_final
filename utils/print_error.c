#include "../includes/minishell.h"

void	print_error_sub1(int error_type, char *opt)
{
	if (error_type == MALLOC_ERROR)
	{
		ft_putstr_fd("malloc ", 2);
		ft_perror(opt);
	}
	else if (error_type == SYNTAX_ERROR)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
	}
	else if (error_type == CMD_NOT_FOUND)
	{
		ft_putstr_fd("cmd not found : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_type == REDIR_INFO_NODE_NOT_FOUND)
	{
		ft_putstr_fd("redirection info not found : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	print_error_sub2(int error_type, char *opt)
{
	if (error_type == REDIR_INFO_NODE_NULL)
	{
		ft_putstr_fd("redirection info node null : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_type == STD_FD_RESTORE_FAIL)
	{
		ft_putstr_fd("std_FD_restore_fail() ", 2);
		ft_perror(opt);
		exit(1);
	}
	else if (error_type == NOT_A_VALID_IDENTIFIER)
	{
		ft_putstr_fd(opt, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	else if (error_type == ERRNO_SET)
	{
		ft_perror(opt);
	}
}

void	print_error_sub3(int error_type, char *opt)
{
	if (error_type == ENV_ARG_ERROR)
	{
		ft_putstr_fd(opt, 2);
		ft_putstr_fd(": No arguments allowed\n", 2);
	}
	else if (error_type == UNSET_ARG_ERROR)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		ft_putstr_fd(opt, 2 );
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("unknown type error\n", 2);
	}
}

void	print_error(int error_type, char *opt)
{
	if (error_type >= REDIR_INFO_NODE_NOT_FOUND)
		print_error_sub1(error_type, opt);
	else if (error_type >= ERRNO_SET)
		print_error_sub2(error_type, opt);
	else
		print_error_sub3(error_type, opt);
}
