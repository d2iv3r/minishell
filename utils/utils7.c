/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:13 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/16 11:58:34 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inside_while(t_params_3 *p)
{
	t_token	*token_holder;

	token_holder = p->tmp_token;
	if (p->tmp_token->type == 1)
	{
		p->fargs[p->i].rdrs[p->x] = p->tmp_token->token_chars;
		p->fargs[p->i].types2[p->x++] = p->tmp_token->type;
		if (p->tmp_token->next)
		{
			p->tmp_token = p->tmp_token->next;
			free(token_holder);
			token_holder = p->tmp_token;
			p->fargs[p->i].rdrs[p->x] = p->tmp_token->token_chars;
			p->fargs[p->i].types2[p->x++] = p->tmp_token->type;
		}
	}
	else
	{
		p->fargs[p->i].args[p->j++] = p->tmp_token->token_chars;
		p->fargs[p->i].types[p->y++] = p->tmp_token->type;
	}
	p->tmp_token = p->tmp_token->next;
	if (token_holder)
		free(token_holder);
}

void	inside_while_0(t_params_3 *p)
{
	t_token	*token_holder;

	token_holder = p->tmp_cmd->head_token;
	p->tmp_token = p->tmp_cmd->head_token->next;
	free(token_holder->token_chars);
	free(token_holder);
	p->fargs[p->i].args = (char **)malloc(sizeof(char *)
			* (ft_lstsize2(p->tmp_token) - ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].rdrs = (char **)malloc(sizeof(char *)
			* (ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].types = (int *)malloc(sizeof(int)
			* (ft_lstsize2(p->tmp_token) - ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].types2 = (int *)malloc(sizeof(int)
			* (ft_count_rdrs(p->tmp_token) + 1));
	p->j = 0;
	p->x = 0;
	p->y = 0;
}

t_fargs	*ft_argnew(t_cmd *commands)
{
	t_params_3	p;

	p.fargs = (t_fargs *)malloc(sizeof(t_fargs) * (ft_lstsize(commands) + 1));
	if (!p.fargs)
		return (0);
	p.tmp_cmd = commands;
	p.i = 0;
	while (p.tmp_cmd)
	{
		p.fargs[p.i].quoted = NULL;
		inside_while_0(&p);
		while (p.tmp_token)
			inside_while(&p);
		p.fargs[p.i].args[p.j] = 0;
		p.fargs[p.i].rdrs[p.x] = 0;
		p.fargs[p.i].quoted = 0;
		p.i++;
		p.tmp_cmd = p.tmp_cmd->next;
	}
	p.fargs[p.i].args = 0;
	return (p.fargs);
}

void	ft_what_will_do_1_01(t_params_5 *p, t_fargs *fargs,
		char **expanded_value)
{
	char	*holder;

	if (fargs[p->i].args[p->j][p->w] == '$' && fargs[p->i].args[p->j][p->w
			+ 1] == '?')
	{
		holder = ft_itoa(g_status);
		p->expanded = ft_strjoin(p->expanded, holder);
		p->x++;
		p->w += 1;
		free(holder);
	}
	else if (fargs[p->i].args[p->j][p->w] == '$'
		&& ft_isalnum(fargs[p->i].args[p->j][p->w + 1]))
	{
		if (p->x < arr_len(expanded_value))
			p->expanded = ft_strjoin(p->expanded, expanded_value[p->x]);
		p->x++;
		p->w += len_till_dollar(fargs[p->i].args[p->j] + p->w + 1);
	}
	else
			p->expanded = add_char(p->expanded, fargs[p->i].args[p->j][p->w]);
		p->w++;
}

void	ft_what_will_do_1(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{
	while (p->w < (int)ft_strlen(fargs[p->i].args[p->j]))
		ft_what_will_do_1_01(p, fargs, expanded_value);
	fargs[p->i].args[p->j] = p->expanded;
	p->j++;
}
