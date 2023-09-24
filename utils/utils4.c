/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:06 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:45:07 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_3(char *start, int *add)
{
	t_params_2	p;

	p.i = 0;
	p.j = 0;
	p.d_lock = 0;
	p.s_lock = 0;
	p.holder = (char *)malloc(ft_strlen(start) + 1);
	dup_3_while(&p, start);
	p.holder[p.j] = 0;
	*add = *add + 0;
	return (ft_strdup(p.holder));
}

void	to_lower_case(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 32;
		i++;
	}
}

void	ft_addbackcmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_cmd	*ft_newcmd(char *head_token)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (0);
	new_cmd->head_token = new_tok(head_token);
	new_cmd->next = NULL;
	return (new_cmd);
}

void	replace_char(char *str, char c1, char c2)
{
	int	i;
	int	d_lock;
	int	s_lock;

	i = 0;
	d_lock = 0;
	s_lock = 0;
	while (str[i])
	{
		if (!d_lock && str[i] == '"')
			d_lock = 1;
		else if (!s_lock && str[i] == '\'')
			s_lock = 1;
		else if (d_lock && str[i] == '"')
			d_lock = 0;
		else if (s_lock && str[i] == '\'')
			s_lock = 0;
		else if (!d_lock && !s_lock && str[i] == c1)
			str[i] = c2;
		i++;
	}
}
