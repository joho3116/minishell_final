#ifndef BUILTIN_H
# define BUILTIN_H
int		builtin_echo(int i);
int		builtin_cd(int i);
int		builtin_pwd(int i);
int		builtin_export(int i);
int		builtin_unset(int i);
int		builtin_env(int i);
int		builtin_exit(int i);

void	builtin_export_sub(int i, int j, bool *error_flag);
#endif
