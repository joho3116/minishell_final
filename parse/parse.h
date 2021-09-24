#ifndef PARSE_H
# define PARSE_H

typedef struct s_list	t_list;

typedef struct s_count_info_in_parse
{
	int		num_of_cmds;
	t_list	*num_of_tokens_in_one_cmd;
}				t_count_info_in_parse;

typedef struct s_redir_lst_nod
{
	int		type;
	char	*path;
}				t_redir_lst_nod;

int		tokenize(char *line);
void	free_in_lex(void);
int		tokenize_return_check(int status);
int		make_string_and_link_node(int mode, char ch);
int		append_char(char **buf, char ch);

void	append_char_sub(char *tmp, char **buf, char ch, int size);
int		at_single_quote(char **line);
int		at_double_quote(char **line);
int		at_redirection_char(char **line);
int		at_white_spaces(char **line);

int		expand_dollar_sign(char **line);
int		expand_exit_status_and_append_string(void);
int		ft_is_in_expansion(char ch);
int		find_env_var_and_mov_ptr(char **line);
int		only_find_env_var(char *start, int len);

int		parse_all(void);
int		free_parsecnt_and_return(int ret, t_count_info_in_parse *parsecnt);
void	free_parse_malloc_in_global_var(void);
int		last_syntax_check(t_count_info_in_parse *parsecnt);

int		count_parse(t_count_info_in_parse *parsecnt, t_list *idx);
int		ft_which_redirection_token(char *str);
int		lst_add_num_of_tokens(t_count_info_in_parse *parsecnt, int token_cnt);
int		*malloc_int_and_set_num(int num);

int		parse_only_redirection(t_list *idx);
int		append_on_redirec_lst_node(t_list **head_of_node, t_list **idx);
int		append_on_redirec_lst_node_sub(t_list **head_of_node, t_list **idx);
int		append_on_redirec_lst_node_sub2(t_list **head_of_node,
			t_list **idx, t_redir_lst_nod *data);

int		lst_add_redirec_lst(t_list *data);
void	fun_clear_redirec_lst_all(void);
void	fun_clear_redirec_lst(void *head);
void	fun_clear_redirec_lst_data(void *data);

int		only_alloc_space_for_cmds(t_count_info_in_parse *parsecnt);
int		only_alloc_space_for_cmds_sub(t_count_info_in_parse *parsecnt);
void	only_alloc_space_for_cmds_sub2(int i, int num_of_nulls);

int		allocate_cmds(t_count_info_in_parse *parsecnt);
int		allocate_cmds_sub(t_list **idx, int *i, int *cmd_i);
void	free_cmds(void);

#endif
