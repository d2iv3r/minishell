/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:52 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:44:49 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_4_hepler_2(t_token **token, t_token **token2, char *word_start,
		int *j)
{
	(*token2)->token_chars = ft_strdup_2(word_start, 1);
	if ((*token))
	{
		(*token)->next = (*token2);
		*j += ft_strlen((*token)->token_chars);
	}
	else
		(*token) = (*token2);
	*j += ft_strlen((*token2)->token_chars);
}

t_token	*make_tokens_4(char *holder, char *word_start, int *j)
{
	t_token	*token;
	t_token	*token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
		token = make_tokens_0(holder, 0);
	token2 = (t_token *)malloc(sizeof(*token2));
	if (!token2)
		return (0);
	token2->type = 1;
	token2->next = NULL;
	if (word_start[1] == word_start[0])
	{
		token_4_hepler(&token, &token2, word_start, j);
		return (token);
	}
	else
	{
		token_4_hepler_2(&token, &token2, word_start, j);
		return (token);
	}
}

void	new_tok_helper(t_params_1 *params, char *word_start)
{
	params->i = 0;
	params->s_lock = 0;
	params->d_lock = 0;
	params->token = NULL;
	params->sign_lock = 0;
	params->holder = (char *)malloc(ft_strlen(word_start) + 2);
	params->holder[0] = 0;
	while (word_start[params->i] == ' ')
		params->i++;
	params->x = 0;
}

t_token	*new_tok_helper_2(t_params_1 *params, int *j)
{
	params->holder[params->x] = 0;
	params->token = (t_token *)malloc(sizeof(*params->token));
	if (!params->token)
		return (0);
	params->token->token_chars = ft_strdup(params->holder);
	*j = *j + params->i;
	params->token->type = 0;
	params->token->next = NULL;
	return (params->token);
}

int	ft_newtok_2(int *j, t_params_1 *params)
{
	*j += 0;
	if (params->sign_lock)
		return (1);
	params->d_lock = 1;
	return (0);
}
