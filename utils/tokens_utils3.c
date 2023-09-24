/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:54 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:40:37 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_newtok_3(int *j, t_params_1 *params)
{
	*j += 0;
	if (params->sign_lock)
		return (1);
	params->s_lock = 1;
	return (0);
}

int	ft_newtok_4(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return (1);
	params->d_lock = 0;
	return (0);
}

int	ft_newtok_5(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return (1);
	params->s_lock = 0;
	return (0);
}

int	ft_newtok_while_3_1(char *str, t_params_1 *p, int *j)
{
	if (str[p->i] == '$' && ft_isalpha(str[p->i + 1]) && !p->s_lock
		&& !p->d_lock)
		return (p->token = make_tokens_1(p->holder, str + p->i, j), 1);
	else if (str[p->i] == '$' && (str[p->i + 1] == '"' || str[p->i + 1] == '\'')
		&& !p->s_lock && !p->d_lock)
		return (p->token = make_tokens_2(p->holder, str + p->i, j), 1);
	else if (str[p->i] == '$' && str[p->i + 1] == '?' && !p->s_lock
		&& !p->d_lock)
		return (p->token = make_tokens_3(p->holder, j), 1);
	else if (!p->s_lock && !p->d_lock && (str[p->i] == '>' || str[p->i] == '<'))
		return (p->token = make_tokens_4(p->holder, str + (p->i), j), 1);
	return (0);
}

int	ft_newtok_while_3(char *str, t_params_1 *p, int *j)
{
	if (p->d_lock && str[p->i] == '"')
	{
		if (ft_newtok_4(j, p))
			return (3);
		return (2);
	}
	else if (p->s_lock && str[p->i] == '\'')
	{
		if (ft_newtok_5(j, p))
			return (3);
		return (2);
	}
	else if (ft_newtok_while_3_1(str, p, j))
		return (1);
	else if (!p->s_lock && !p->d_lock && str[p->i] == ' ')
		return (2);
	if (str[p->i] == '$')
		p->sign_lock = 1;
	p->holder[p->x++] = str[p->i];
	p->holder[p->x] = 0;
	return (0);
}
