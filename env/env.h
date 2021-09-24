#ifndef ENV_H
# define ENV_H

typedef struct s_env_node
{
	char	*key;
	char	*value;
}				t_env_node;

int			init_minishell_envp(char *envp[]);
void		malloc_and_strcpy_key_value(char *env, char **key, char **value);
t_env_node	*make_env_node(char **key, char **value);
int			ft_key_len(char *str);
char		*duplicate_only_value(char *key_value);

int			set_new_value_to_existing_key(char *key, char *new_value);
void		find_key_and_unset(char *key);
int			set_new_key(char *key_and_value);
int			set_new_key_malloc_error_return(void);
char		**get_env_list(void);

char		**get_env_list_with_quotation(void);
int			count_env_num_all(void);
int			count_env_num_exclude_null_value(void);
char		*unite_key_value(t_list *idx);
char		*unite_key_value_with_quotation(t_list *idx);

void		free_envp_list(char **envp);
char		*find_key_and_return_value(char *key);
t_list		*find_key_and_return_node(char *key);

#endif
