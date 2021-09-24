#ifndef PIPE_H
# define PIPE_H

# define BUF_SIZE 10

int		run_cmd(void);

int		is_builtin(char *str);

int		run_only_one_cmd_builtin_error_return(int i, int error_check);
int		builtin_sort(int i);
int		run_only_one_cmd(int i);
int		run_only_one_cmd_builtin(int i);

void	copy_pipe_fd(int a[], int b[]);
int		num_of_cmd(void);

void	run_pipe_init(int pipes[2][2], int stat_pid_i[3]);
int		run_pipe(void);
int		run_pipe_loop(int stat_pid_i[3], int pipes[2][2], int *child_stat);
int		run_pipe_return(int stat_pid_i[3], int *child_stat,
			char **sys_siglist);
void	print_sig_error(char *sys_siglist[], int *child_stat, int i);
void	pipe_child(int i, int pipe0[2], int pipe1[2]);
void	pipe_child_sub(int i, int pipe1[2]);
void	pipe_parent(int stat_pid_i[3], int pipes[2][2], int *child_stat);
int		restore_stdin_stdout(void);

int		check_input_redirection(int i, int pip[]);

void	check_input_redir_heredoc(int pip[], t_list *node_of_redir_list);
int		check_input_redir_from_file(int pip[], t_list *node_of_redir_list);

int		check_output_redirection(int i, int pip[]);
int		check_output_redirection_sub(int pip[], t_list *node_of_redir_list);

void	try_builtin_or_execve(int i);

int		try_builtin_or_execve_sub(int i, char **envp);

char	*try_builtin_or_execve_sub2(int *path_string_idx, int path_idx,
			int i, char **envp);

int		find_index_of_path_in_env(char **envp);

char	*pipe_strjoin(char *s1, char *s2, char *s3);

#endif
