#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>

# include "../parse/parse.h"
# include "../utils/utils.h"
# include "../pipe/pipe.h"
# include "../builtin/builtin.h"
# include "../env/env.h"
# include "../main/main.h"

# define STDIN_BACKUP_FD 3
# define STDOUT_BACKUP_FD 4

# define NORMAL 0
# define LEX_FINAL_W_CHAR 1
# define LEX_FINAL_WO_CHAR 2
# define LEX_FOR_FREE 3

# define MALLOC_ERROR -2
# define SYNTAX_ERROR -3
# define CMD_NOT_FOUND -4
# define REDIR_INFO_NODE_NOT_FOUND -5
# define REDIR_INFO_NODE_NULL -6
# define OPEN_ERROR -7
# define HOME_NOT_FOUND -8
# define STD_FD_RESTORE_FAIL -9
# define NOT_A_VALID_IDENTIFIER -10
# define ERRNO_SET -11
# define ENV_ARG_ERROR -12
# define UNSET_ARG_ERROR -13

# define IN_REDIR 11
# define OUT_REDIR 12
# define IN_REDIR_LIM 13
# define OUT_REDIR_APP 14
# define PIPE 15
# define NOT_REDIR 16

# define NO_REDIR_FOR_CMD 0

typedef struct s_info
{
	t_list			*lex_head;
	t_list			*env;
	unsigned int	exit_status;
	char			***cmds;
	t_list			*cmd_redir_lst;
	int				num_of_cmds;
}				t_info;

extern t_info	g_info;
bool	is_only_white_spaces(char *line);

void	rl_replace_line(const char *text, int clear_undo);

#endif
