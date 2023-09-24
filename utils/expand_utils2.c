/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:42 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 15:36:47 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand2_while_while(t_params_4 *p, t_env *env, char **e_v)
{
	p->j = 0;
	p->did = 0;
	while (env[p->j].var)
	{
		if ((int)ft_strlen(env[p->j].var) == len_till_dollar(p->cpy
				+ p->i + 1) && !ft_strncmp(env[p->j].var, p->cpy + p->i
				+ 1, ft_strlen(env[p->j].var)))
		{
			append_to_value_arr(e_v, ft_strdup(env[p->j].value));
			p->did = 1;
			break ;
		}
		p->j++;
	}
}

void	ft_expand2_while(t_params_4 *p, t_env *env, char **e_v, int her)
{
	while (p->i++ < (int)ft_strlen(p->cpy))
	{
		if (p->cpy[p->i] == '\'')
			p->s_lock = !p->s_lock;
		if (p->cpy[p->i] == '$' && p->s_lock && her)
			append_to_value_arr(e_v, ft_strdup_ex(p->cpy + p->i + 1));
		else if (p->cpy[p->i] == '$' && (p->cpy[p->i]
				&& (ft_isalnum(p->cpy[p->i + 1]) || p->cpy[p->i + 1] == '?')))
		{
			if (p->cpy[p->i + 1] == '?')
				append_to_value_arr(e_v, ft_itoa(g_status));
			else
			{
				ft_expand2_while_while(p, env, e_v);
				if (!p->did)
					append_to_value_arr(e_v, ft_strdup(""));
			}
		}
	}
}

int	ft_expand2(char **word, t_env *env, char **e_v, int her)
{
	t_params_4	p;

	set_expand2_values(&p, word);
	ft_expand2_while(&p, env, e_v, her);
	return (0);
}

int	has_expand(char *token)
{
	int	i;
	int	d_lock;
	int	s_lock;

	i = 0;
	d_lock = 0;
	s_lock = 0;
	while (token[i])
	{
		if (token[i] == '$' && !d_lock && !s_lock)
			return (1);
		if (token[i] == '"' && !s_lock)
			d_lock = !d_lock;
		else if (token[i] == '"' && !d_lock)
			s_lock = !s_lock;
		i++;
	}
	return (0);
}
