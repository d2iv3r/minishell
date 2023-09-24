/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:46 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/12 15:13:38 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSSING_UTILS_H
# define PARSSING_UTILS_H

# include "../minishell.h"

typedef struct s_env			t_env;
typedef struct s_params_10		t_params_10;
typedef struct s_params_9		t_params_9;
typedef struct s_params_8		t_params_8;
typedef struct s_params_7		t_params_7;
typedef struct s_params_6		t_params_6;
typedef struct s_params_5		t_params_5;
typedef struct s_params_4		t_params_4;
typedef struct s_params_3		t_params_3;
typedef struct s_params_2		t_params_2;
typedef struct s_params_1		t_params_1;
typedef struct s_token			t_token;
typedef struct s_fargs			t_fargs;
typedef struct s_main_params	t_main_params;
typedef struct s_cmd			t_cmd;

//utils 1
int		arr_len(char **arr);
int		len_till_dollar(char *str);
int		how_many_dollars(char *str);
void	append_to_value_arr(char **arr, char *new_value);
void	free_arr(char **arr);

//utils 2
void	remove_empty(char **args);
void	ft_empty_removal(t_fargs *fargs);
void	split_while_1(t_params_7 *p, char **arr, int *types);
void	split_while_2(t_params_7 *p, char **arr, int *types);
char	**do_split(char **arr, int *types);

//utils 3
char	**add_to_arr(char ***arr, char *new_value);
int		rdr_while(t_fargs *fargs, int len, int i, int j);
int		ambiguos(char **rdrs);
int		ft_check_rdr(t_fargs *fargs);
char	*add_char(char *str, char c);

//utils 4
char	*ft_strdup_3(char *start, int *add);
void	to_lower_case(char *word);
void	ft_addbackcmd(t_cmd **head, t_cmd *new);
t_cmd	*ft_newcmd(char *head_token);
void	replace_char(char *str, char c1, char c2);

//utils 5
char	*ft_strdup_ex(char *start);
char	*ft_strdup_2(char *start, int len);
void	dup_3_while(t_params_2 *p, char *start);
int		ft_lstsize(t_cmd *cmd);
int		ft_lstsize2(t_token *token);

//utils 6
void	ft_what_will_do_2(t_params_5 *p, t_fargs *fargs, char **expanded_value);
void	while_1(t_params_5 *p, t_fargs *fargs, char **expanded_value);
void	what_will_do_helper(t_fargs *fargs, char **expanded_value,
			t_params_5 *p);
void	what_will_do_helper2(t_fargs *fargs, char **expanded_value,
			t_params_5 *p);
int		ft_what_will_do(t_fargs *fargs, char **expanded_value);

//utils 7
int		ft_count_rdrs(t_token *start);
void	inside_while(t_params_3 *p);
void	inside_while_0(t_params_3 *p);
t_fargs	*ft_argnew(t_cmd *commands);
void	ft_what_will_do_1(t_params_5 *p, t_fargs *fargs, char **expanded_value);
void	ft_what_will_do_while(t_params_5 *p, t_fargs *fargs,
			char **expanded_value);

//utils 8
void	quotes_while(char **splitted, t_params_6 *p);
void	print_list(t_cmd *commands);
void	print_struct(t_fargs *fargs);
int		check_pipes(char *line);
void	ft_addback(t_token **head, t_token *new);

//tokens_utils
t_token	*make_tokens_0(char *holder, int type);
t_token	*make_tokens_1(char *holder, char *word_start, int *j);
t_token	*make_tokens_2(char *holder, char *word_start, int *j);
t_token	*make_tokens_3(char *holder, int *j);
void	token_4_hepler(t_token **token, t_token **token2, char *word_start,
			int *j);

//tokens_utils 2
void	token_4_hepler_2(t_token **token, t_token **token2, char *word_start,
			int *j);
t_token	*make_tokens_4(char *holder, char *word_start, int *j);
void	new_tok_helper(t_params_1 *params, char *word_start);
t_token	*new_tok_helper_2(t_params_1 *params, int *j);
int		ft_newtok_2(int *j, t_params_1 *params);

//tokens_utils 3
int		ft_newtok_3(int *j, t_params_1 *params);
int		ft_newtok_4(int *j, t_params_1 *params);
int		ft_newtok_5(int *j, t_params_1 *params);
int		ft_newtok_while_3_1(char *str, t_params_1 *p, int *j);
int		ft_newtok_while_3(char *str, t_params_1 *p, int *j);

//tokens_utils 4
int		ft_newtok_while_2(char *word_start, t_params_1 *params, int *j);
t_token	*ft_newtok_while(char *word_start, t_params_1 *params, int *j);
t_token	*ft_newtok(char *word_start, int *j);
t_token	*new_tok(char *chars);
void	ft_make_tokens_initial(t_params_10 *p, char *holder);

//tokens_utils 5
void	ft_make_tokens_inside(t_params_10 *p, char *holder, char *cmd);
void	make_tokens_while(t_params_10 *p, char *cmd, char *holder);
char	**ft_make_tokens(char *cmd);
t_token	*make_tok0(char *chars);

//expand_utils
void	set_expand2_values(t_params_4 *p, char **word);
void	inside_while_expand(t_params_4 *p, char **expanded_values);
void	expand_helper(t_params_4 *p);
int		expand_helper_2(char **env, t_params_4 *p, char **e_v);
int		ft_expand(char **word, char **env);

//expand_utils 2
void	ft_expand2_while(t_params_4 *p, t_env *env, char **e_v, int her);
int		ft_expand2(char **word, t_env *env, char **e_v, int her);
int		has_expand(char *token);

//herdoc_utils
void	herdoc_while(t_params_8 *p, char **buff);
void	herdoc_01(t_params_8 *p, t_env *env_2, char **buff);
char	**exp_herdoc_value(char **buff, t_env *env_2);
void	read_lines(char ***buff, t_fargs *fargs, int j, int *xpand);
char	**get_herdoc_value(t_fargs *f_args, int *xpand);
char	**add_new_line(char **arr2d, char *line);

//quotes_utils
int		has_quotes(char *token);
char	*remove_quotes(char *token);
void	ft_quotes_removal_2(t_fargs *fargs);
void	ft_quotes_removal(t_fargs *fargs);
int		ft_quotes(char **splitted);

//cleaning
void	free_cmds(t_cmd *cmds);
void	free_fargs(t_fargs *fargs);
void	main_free_2(t_main_params *p);
void	main_free(t_main_params *p);

#endif
