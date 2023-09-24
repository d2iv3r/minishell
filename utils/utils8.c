/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:15 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 20:24:00 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_while(char **splitted, t_params_6 *p)
{
	while (splitted[p->i][p->j])
	{
		if (p->d_lock && splitted[p->i][p->j] == '\'')
		{
			p->j++;
			continue ;
		}
		else if (p->s_lock && splitted[p->i][p->j] == '"')
		{
			p->j++;
			continue ;
		}
		else if (!p->d_lock && splitted[p->i][p->j] == '"')
			p->d_lock = 1;
		else if (!p->s_lock && splitted[p->i][p->j] == '\'')
			p->s_lock = 1;
		else if (p->d_lock && splitted[p->i][p->j] == '"')
			p->d_lock = 0;
		else if (p->s_lock && splitted[p->i][p->j] == '\'')
			p->s_lock = 0;
		p->j++;
	}
}

void	print_list(t_cmd *commands)
{
	t_cmd	*tmp;
	t_token	*token;

	tmp = commands;
	while (tmp)
	{
		token = tmp->head_token;
		while (token)
		{
			token = token->next;
		}
		tmp = tmp->next;
	}
}

int	check_pipes(char *line)
{
	int		i;
	int		s_lock;
	int		d_lock;
	char	*line2;

	i = 0;
	s_lock = 0;
	d_lock = 0;
	line2 = ft_strtrim(line);
	if (!line[0])
		return (0);
	if (line2[i] == '|' || line2[ft_strlen(line2) - 1] == '|')
	{
		printf("minishell: parse error near `|'\n");
		free(line2);
		return (g_status = 258, 1);
	}
	while (line2[i] && line2[i] != '|')
		i++;
	if (i < (int)ft_strlen(line2) && check_pipes(line2 + i + 1))
		return (free(line2), g_status = 258, 1);
	return (free(line2), 0);
}

void	ft_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

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

void	ft_what_will_do_while(t_params_5 *p, t_fargs *fargs,
		char **expanded_value)
{
	while (fargs[p->i].rdrs[p->j][p->w])
	{
		if (fargs[p->i].rdrs[p->j][p->w] == '$'
			&& (ft_isalnum(fargs[p->i].rdrs[p->j][p->w + 1])
				|| fargs[p->i].rdrs[p->j][p->w + 1] == '?'))
		{
			if (expanded_value[p->x])
				p->expanded = ft_strjoin(p->expanded, expanded_value[p->x]);
			p->x++;
			p->w += len_till_dollar(fargs[p->i].rdrs[p->j] + p->w + 1);
			if (fargs[p->i].rdrs[p->j][p->w + 1] == '?')
				p->w += 1;
			p->did_expand = 1;
		}
		else
			p->expanded = add_char(p->expanded,
					fargs[p->i].rdrs[p->j][p->w]);
		p->w++;
	}
}
