/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:48 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/13 15:26:40 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_quotes(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *token)
{
	t_params_9	p;
	char		*holder;

	p.i = 0;
	p.s_lock = 0;
	p.d_lock = 0;
	p.x = 0;
	holder = (char *)malloc(ft_strlen(token) + 1);
	if (!holder)
		exit(1);
	while (token[p.i])
	{
		if (p.d_lock && token[p.i] == '\'')
			holder[p.x++] = token[p.i];
		else if (p.s_lock && token[p.i] == '"')
			holder[p.x++] = token[p.i];
		else if (token[p.i] == '"')
			p.d_lock = !p.d_lock;
		else if (token[p.i] == '\'')
			p.s_lock = !p.s_lock;
		else
			holder[p.x++] = token[p.i];
		p.i++;
	}
	return (holder[p.x] = 0, free(token), holder);
}

void	ft_quotes_removal_2(t_fargs *fargs)
{
	int	i;
	int	j;
	int	s_lock;
	int	d_lock;

	i = 0;
	s_lock = 0;
	d_lock = 0;
	while (fargs[i].args)
	{
		j = 0;
		while (fargs[i].args[j])
		{
			fargs[i].args[j] = remove_quotes(fargs[i].args[j]);
			j++;
		}
		j = 0;
		while (fargs[i].rdrs[j])
		{
			fargs[i].rdrs[j] = remove_quotes(fargs[i].rdrs[j]);
			j++;
		}
		i++;
	}
}

void	ft_quotes_removal(t_fargs *fargs)
{
	int	i;
	int	j;
	int	x;
	int	*arr;

	i = 0;
	while (fargs[i].args)
	{
		arr = (int *)malloc(sizeof(int) * (arr_len(fargs[i].rdrs)));
		if (!arr)
			exit(1);
		x = 0;
		j = 0;
		j = 0;
		while (fargs[i].rdrs[j])
		{
			arr[j] = has_quotes(fargs[i].rdrs[j]);
			j++;
		}
		fargs[i].quoted = arr;
		i++;
	}
	ft_quotes_removal_2(fargs);
	ft_empty_removal(fargs);
}

int	ft_quotes(char **splitted)
{
	t_params_6	p;

	p.i = 0;
	while (splitted[p.i])
	{
		p.s_lock = 0;
		p.d_lock = 0;
		p.j = 0;
		quotes_while(splitted, &p);
		if (p.d_lock || p.s_lock)
		{
			printf("did not handle quotes. <%s>\n", splitted[p.i]);
			free_arr(splitted);
			return (1);
		}
		p.i++;
	}
	return (0);
}
