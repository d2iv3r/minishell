/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:07:50 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 11:39:46 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executer/executer.h"
# include "utils/parssing_utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

int						g_status;

typedef struct s_token
{
	char				*token_chars;
	int					type;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	t_token				*head_token;
	char				**tokens;
	int					s_quotes;
	int					d_quotes;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_fargs
{
	char				**args;
	int					infile;
	int					outfile;
	int					sig_herdoc;
	int					incpy;
	char				*tmp_file;
	char				**rdrs;
	int					*types;
	int					*types2;
	int					*quoted;
}						t_fargs;

// norm helpers

typedef struct s_params_1
{
	t_token				*token;
	int					i;
	int					x;
	int					sign_lock;
	int					s_lock;
	int					d_lock;
	char				*holder;
}						t_params_1;

typedef struct s_params_2
{
	int					i;
	int					d_lock;
	int					s_lock;
	int					j;
	char				*holder;
}						t_params_2;

typedef struct s_params_3
{
	t_fargs				*fargs;
	t_cmd				*tmp_cmd;
	t_token				*tmp_token;
	int					i;
	int					j;
	int					x;
	int					y;
}						t_params_3;

typedef struct s_params_4
{
	int					i;
	int					j;
	int					did;
	char				*cpy;
	int					s_lock;
	int					d_lock;
}						t_params_4;

typedef struct s_params_5
{
	int					i;
	int					j;
	int					x;
	int					w;
	int					t;
	int					args_len;
	int					a_n_f_len;
	char				*expanded;
	int					did_expand;
	char				**holder;
}						t_params_5;

typedef struct s_params_6
{
	int					i;
	int					j;
	int					s_lock;
	int					d_lock;
}						t_params_6;

typedef struct s_params_7
{
	int					i;
	char				**splitted;
	char				**new;
	int					len;
	int					j;
}						t_params_7;

typedef struct s_params_8
{
	char				**her_values;
	char				**expanded_her;
	int					len;
	int					j;
	int					i;
	int					x;
	int					z;
	int					t;
	char				holder[100000];
}						t_params_8;

typedef struct s_params_9
{
	int					i;
	int					d_lock;
	int					s_lock;
	int					x;
}						t_params_9;

typedef struct s_params_10
{
	int					i;
	int					d_lock;
	int					s_lock;
	char				**tokens;
	int					x;
	char				holder[100000];
}						t_params_10;

typedef struct s_main_params
{
	char				*input;
	char				**splited_cmds;
	int					i;
	int					j;
	t_cmd				*commands;
	t_cmd				*cmd_head_holder;
	t_fargs				*fargs;
	char				**exp;
	char				**expanded_values;
	char				*input_holder;
	t_env				*env_2;
	struct sigaction	sig;
	char				**herdoc;
	int					xxx;
}						t_main_params;

typedef struct s_env	t_env;

// LIBFT
char					**ft_split(char const *s, char c);
size_t					ft_strlen(const char *str);
char					*ft_strjoin(char *s1, char const *s2);
char					*ft_strjoin_3(char const *s1, char const *s2);
char					*ft_strdup(const char *s1);
char					*ft_strtrim(char const *s1);
char					**exp_herdoc_value(char **buff, t_env *env_2);

int						arr_len(char **arr);
void					check_max(char **rdrs);
int						len_till_dollar(char *str);
int						how_many_dollars(char *str);
void					append_to_value_arr(char **arr, char *new_value);
void					free_arr(char **arr);
void					sig_herdoc(int sig);
void					sig_handler(int sig);
void					main_intial_values(t_main_params *p, char **env);
void					main_while_inside_while(t_main_params *p);
void					main_inside_while(t_main_params *p);

#endif
