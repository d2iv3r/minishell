/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:56 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:40:38 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_newtok_while_2(char *word_start, t_params_1 *params, int *j)
{
	if (params->d_lock && word_start[params->i] == '\''
		&& word_start[params->i + 1] != '$')
		return (params->holder[params->x++] = word_start[params->i], 2);
	else if (params->s_lock && word_start[params->i] == '"'
		&& word_start[params->i + 1] != '$')
		return (params->holder[params->x++] = word_start[params->i], 2);
	else if (!params->d_lock && word_start[params->i] == '"')
	{
		if (ft_newtok_2(j, params))
			return (1);
		return (2);
	}
	else if (!params->s_lock && word_start[params->i] == '\'')
	{
		if (ft_newtok_3(j, params))
			return (1);
		return (2);
	}
	return (0);
}

t_token	*ft_newtok_while(char *word_start, t_params_1 *params, int *j)
{
	int	helper;

	while (word_start[params->i])
	{
		helper = ft_newtok_while_2(word_start, params, j);
		if (helper == 1)
			break ;
		else if (helper == 2)
		{
			helper = 2;
		}
		else
		{
			helper = ft_newtok_while_3(word_start, params, j);
			if (helper == 1)
				return (params->token);
			if (helper)
				break ;
		}
		params->i++;
	}
	return (params->token);
}

t_token	*ft_newtok(char *word_start, int *j)
{
	t_params_1	params;

	printf("word start [i] == %c\n", word_start[0]);
	new_tok_helper(&params, word_start);
	if (ft_newtok_while(word_start, &params, j))
	{
		return (params.token);
	}
	while (word_start[params.i] == ' ')
		params.i++;
	return (new_tok_helper_2(&params, j));
}

t_token	*new_tok(char *chars)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->token_chars = ft_strdup(chars);
	token->type = 0;
	token->next = NULL;
	return (token);
}

void	ft_make_tokens_initial(t_params_10 *p, char *holder)
{
	p->i = 0;
	p->d_lock = 0;
	p->s_lock = 0;
	p->tokens = (char **)malloc(sizeof(char *));
	p->tokens[0] = 0;
	p->x = 0;
	holder[0] = 0;
}
