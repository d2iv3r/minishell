/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:50 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 18:40:33 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*make_tokens_0(char *holder, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(*token));
	if (!token)
		return (0);
	token->token_chars = ft_strdup(holder);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*make_tokens_1(char *holder, char *word_start, int *j)
{
	t_token	*token;
	t_token	*token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
		token = make_tokens_0(holder, 0);
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return (0);
	token2->token_chars = ft_strdup_2(word_start,
			len_till_dollar(word_start + 1) + 1);
	token2->type = 2;
	token2->next = NULL;
	if (ft_strlen(holder))
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + ft_strlen(token2->token_chars);
	return (token);
}

t_token	*make_tokens_2(char *holder, char *word_start, int *j)
{
	t_token	*token;
	t_token	*token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
		token = make_tokens_0(holder, 0);
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return (0);
	token2->token_chars = ft_strdup_3(word_start + 1, j);
	token2->type = 2;
	token2->next = NULL;
	if (token)
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + 1;
	return (token);
}

t_token	*make_tokens_3(char *holder, int *j)
{
	t_token	*token;
	t_token	*token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
		token = make_tokens_0(holder, 0);
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return (0);
	token2->token_chars = ft_strdup("$?");
	token2->type = 2;
	token2->next = NULL;
	if (token)
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + 2;
	return (token);
}

void	token_4_hepler(t_token **token, t_token **token2, char *word_start,
		int *j)
{
	(*token2)->token_chars = ft_strdup_2(word_start, 2);
	if ((*token))
	{
		(*token)->next = (*token2);
		*j += ft_strlen((*token)->token_chars);
	}
	else
		(*token) = (*token2);
	*j += ft_strlen((*token2)->token_chars);
}
