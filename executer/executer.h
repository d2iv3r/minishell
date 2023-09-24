/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:29:42 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 22:12:07 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/errno.h>
# include <string.h>
# include "../minishell.h"

typedef struct s_fargs	t_fargs;

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

# define OPEN_PIPE 2
# define CLOSE_CH 0
# define CLOSE_P 1

//struct for enverenement
typedef struct s_env
{
	char	*var;
	char	*value;
}			t_env;

//Builtins
int		ft_builtins(t_fargs *f_args, int i, t_env **env, int builtins_no);
int		ft_echo(char **args, int fd);
int		ft_cd(char **arg, t_env **env);
int		ft_pwd(int fd);
int		ft_export(t_fargs *f_args, t_env **env);
int		ft_unset(t_fargs *f_args, t_env **env);
int		ft_env(char **args, t_env *env, int fd);
void	ft_exit(char **args);
char	*add1_shlvl(char *value);
int		is_builtins(char **cmd);

// Builtins utils
int		exist_var(t_env *env, char *arg);
int		len_arr2d(char **arr2d);
char	*get_var(char *line);
char	*get_value(char *line);
t_env	*get_env(char **env);
void	print_env(t_env *env, int fd);
int		len_var(char *line);
int		len_tenv(t_env	*env);
t_env	*add_var(t_env *env, char *arg);

//Executing
void	ft_execute(t_fargs *f_args, t_env **env, char **herdoc);

//Executing utils
int		print_error(char *args, char *err, int stat, int ret);
int		get_infile(t_fargs *fargs, int i, char **herdoc);
int		get_outfile(char **redr, int *outf);
int		is_executable(char *arg, t_env *env);
char	*g_exe(char *cmd, t_env *env);
char	*get_access_path(char *path, char *arg);
int		open_close(t_fargs *f_args, int i, int oc);
char	**t_env_to_arr2d(t_env *env);
void	wait_childs(int pid);
char	*ft_strjoin_2(char *s1, char *s2, int clean);

// mr.clean
void	clean_env(t_env *env);
void	clean_arr2d(char **arr2d);

#endif
