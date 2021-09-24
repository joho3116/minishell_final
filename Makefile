NAME		=	minishell

SRCS		= 	main/main.c\
				builtin/ft_cd.c\
				builtin/ft_echo.c\
				builtin/ft_env.c\
				builtin/ft_exit.c\
				builtin/ft_export.c\
				builtin/ft_pwd.c\
				builtin/ft_unset.c\
				env/env.c\
				env/env2.c\
				env/env3.c\
				env/env4.c\
				parse/lex.c\
				parse/lex2.c\
				parse/lex3.c\
				parse/parse.c\
				parse/parse_allocate_cmds.c\
				parse/parse_count_parse.c\
				parse/parse_only_alloc_space_for_cmds.c\
				parse/parse_parse_only_redirection.c\
				parse/parse_parse_only_redirection2.c\
				pipe/pipe.c\
				pipe/pipe2.c\
				pipe/pipe3.c\
				pipe/pipe4.c\
				pipe/pipe5.c\
				pipe/pipe6.c\
				utils/find_node_at_idx_in_lst.c\
				utils/ft_perror.c\
				utils/print_error.c\
				utils/safe_free.c\
				utils/signal.c

OBJS		=	$(SRCS:.c=.o)

SRCDIR		=	./builtin\
				./env\
				./main\
				./parse\
				./pipe\
				./utils

LEAKS		=	-g3 -fsanitize=address

LIBFT		=	libft/libft.a

HEADERS		=	includes/minishell.h\
				builtin/builtin.h\
				env/env.h\
				parse/parse.h\
				pipe/pipe.h\
				utils/utils.h

CFLAGS	= 	-Wall -Wextra -Werror -g

CC		=	gcc

RM		=	rm -rf

ifdef LOCALMAC
	LIBS	=	-lreadline -L/usr/local/opt/readline/lib
	HEADER_DIR = -I./includes -I/usr/local/opt/readline/include/readline
else
	ifdef USER
		LIBS	=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib
		HEADER_DIR = -I./includes -I/Users/$(USER)/.brew/opt/readline/include/readline
	else
		LIBS	=	-lreadline -L /Users/chanlee/.brew/opt/readline/lib
		HEADER_DIR = -I/Users/chanlee/.brew/opt/readline/include
	endif
endif

all				: $(NAME)

$(LIBFT)		:
	$(MAKE) -C ./libft

%.o				: %.c $(HEADERS)
	$(CC) $< $(HEADER_DIR) $(CFLAGS) -c -o $@

$(NAME)			: $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADER_DIR) $(CFLAGS) -o $(NAME)

clean			:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean			: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re				: fclean all
