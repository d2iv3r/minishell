/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:08 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:40:49 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_ex(char *start)
{
	char	*ret;
	int		i;
	int		len;

	len = len_till_dollar(start);
	ret = (char *)malloc(len + 2);
	if (!ret)
		exit(1);
	ret[0] = '$';
	i = 0;
	while (i < len && ft_isalpha(start[i]))
	{
		ret[i + 1] = start[i];
		i++;
	}
	ret[i + 1] = 0;
	return (ret);
}

char	*ft_strdup_2(char *start, int len)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(len + 1);
	while (i < len)
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	dup_3_while(t_params_2 *p, char *start)
{
	while (start[p->i] && ft_isalpha(start[p->i]))
	{
		if (p->d_lock && start[p->i] == '\'')
			p->holder[p->j++] = start[p->i];
		else if (p->s_lock && start[p->i] == '"')
			p->holder[p->j++] = start[p->i];
		else if (!p->d_lock && start[p->i] == '"')
			p->d_lock = 1;
		else if (!p->s_lock && start[p->i] == '\'')
			p->s_lock = 1;
		else if (p->d_lock && start[p->i] == '"')
			p->d_lock = 0;
		else if (p->s_lock && start[p->i] == '\'')
			p->s_lock = 0;
		else if (!p->s_lock && !p->d_lock && start[p->i] == ' ')
			break ;
		else
			p->holder[p->j++] = start[p->i];
		p->i++;
	}
}

int	ft_lstsize(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	ft_lstsize2(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
