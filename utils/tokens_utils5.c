/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:58 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/13 12:36:09 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_make_tokens_inside(t_params_10 *p, char *holder, char *cmd)
{
	holder[p->x] = 0;
	if (p->x)
		add_to_arr(&p->tokens, ft_strdup(holder));
	p->x = 0;
	if (cmd[p->i] == cmd[p->i + 1])
	{
		add_to_arr(&p->tokens, ft_strdup_2(cmd + p->i, 2));
		p->i += 1;
	}
	else
		add_to_arr(&p->tokens, ft_strdup_2(cmd + p->i, 1));
	p->i++;
}

void	make_tokens_while(t_params_10 *p, char *cmd, char *holder)
{
	while (cmd[p->i])
	{
		if (cmd[p->i] == '"')
			p->d_lock = !p->d_lock;
		else if (cmd[p->i] == '\'')
			p->s_lock = !p->s_lock;
		else if (!p->s_lock && !p->d_lock && cmd[p->i] == ' ')
		{
			holder[p->x] = 0;
			if (p->x)
				add_to_arr(&p->tokens, ft_strdup(holder));
			p->x = 0;
			p->i++;
			continue ;
		}
		else if (!p->s_lock && !p->d_lock && (cmd[p->i] == '>'
				|| cmd[p->i] == '<'))
		{
			ft_make_tokens_inside(p, holder, cmd);
			continue ;
		}
		holder[p->x++] = cmd[p->i];
		p->i++;
	}
}

char	**ft_make_tokens(char *cmd)
{
	t_params_10	p;

	ft_make_tokens_initial(&p, p.holder);
	make_tokens_while(&p, cmd, p.holder);
	if (p.x)
	{
		p.holder[p.x] = 0;
		add_to_arr(&p.tokens, ft_strdup(p.holder));
	}
	return (p.tokens);
}

t_token	*make_tok0(char *chars)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->token_chars = chars;
	if (!ft_strcmp(chars, ">>")
		|| !ft_strcmp(chars, ">") || !ft_strcmp(chars, "<<")
		|| !ft_strcmp(chars, "<"))
		token->type = 1;
	else if (has_expand(chars))
		token->type = 2;
	else
		token->type = 0;
	token->next = NULL;
	return (token);
}
