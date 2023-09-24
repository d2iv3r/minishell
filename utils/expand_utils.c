/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:40 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:39:41 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_expand2_values(t_params_4 *p, char **word)
{
	p->i = -1;
	p->j = 0;
	p->did = 0;
	p->s_lock = 0;
	p->d_lock = 0;
	p->cpy = *word;
}

void	inside_while_expand(t_params_4 *p, char **expanded_values)
{
	if (p->did)
		p->i += len_till_dollar(p->cpy + p->i + 1) + 1;
	else if (p->cpy[p->i] == '$' && ft_isalpha(p->cpy[p->i + 1]))
	{
		append_to_value_arr(expanded_values, ft_strdup(""));
		p->i++;
	}
	else
		p->i++;
}

void	expand_helper(t_params_4 *p)
{
	p->j = 0;
	while (p->cpy[p->i] && p->cpy[p->i] != '$' && ft_isalpha(p->cpy[p->i + 1]))
		p->i++;
}

int	expand_helper_2(char **env, t_params_4 *p, char **e_v)
{
	if (!ft_strncmp(env[p->j], p->cpy + p->i + 1, len_till_dollar(p->cpy + p->i
				+ 1)) && env[p->j][len_till_dollar(p->cpy + p->i + 1)] == '=')
	{
		p->did = 1;
		append_to_value_arr(e_v, ft_strdup(env[p->j] + len_till_dollar(p->cpy
					+ p->i + 1) + 1));
		return (1);
	}
	return (0);
}

int	ft_expand(char **word, char **env)
{
	char	*hold_to_free;
	int		found_var;
	int		i;

	found_var = 0;
	hold_to_free = *word;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(*word + 1, env[i], ft_strlen(*word + 1)))
		{
			found_var = 1;
			*word = ft_strdup(env[i] + ft_strlen(*word));
			if (!*word)
				return (1);
			break ;
		}
		i++;
	}
	if (!found_var)
		*word[0] = 0;
	if (!*word)
		return (1);
	return (0);
}
