/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:02 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/12 15:40:07 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_empty(char **args)
{
	int		i;
	int		j;
	char	*holder;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (!args[i][0])
		{
			holder = args[i];
			j = i;
			while (args[j + 1])
			{
				args[j] = args[j + 1];
				j++;
			}
			args[j] = 0;
			free(holder);
		}
		i++;
	}
}

void	ft_empty_removal(t_fargs *fargs)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (fargs[++i].args)
		remove_empty(fargs[i].args);
}

void	split_while_1(t_params_7 *p, char **arr, int *types)
{
	while (arr[p->i])
	{
		if (types[p->i] == 2)
		{
			p->splitted = ft_split(arr[p->i], ' ');
			if (!p->splitted)
				exit(1);
			p->len += arr_len(p->splitted);
			free_arr(p->splitted);
		}
		else
			p->len++;
		p->i++;
	}
}

void	split_while_2(t_params_7 *p, char **arr, int *types)
{
	while (arr[p->i])
	{
		if (types[p->i] == 2)
		{
			p->splitted = ft_split(arr[p->i], ' ');
			if (!p->splitted)
				exit(1);
			p->j = 0;
			while (p->splitted[p->j])
			{
				p->new[p->len] = ft_strdup(p->splitted[p->j]);
				p->j++;
				p->len++;
			}
			free_arr(p->splitted);
		}
		else
		{
			p->new[p->len] = ft_strdup(arr[p->i]);
			p->len++;
		}
		p->i++;
	}
}

char	**do_split(char **arr, int *types)
{
	t_params_7	p;

	p.i = 0;
	p.len = 0;
	split_while_1(&p, arr, types);
	p.new = (char **)malloc(sizeof(char *) * (p.len + 1));
	if (!p.new)
		exit(1);
	p.i = 0;
	p.len = 0;
	split_while_2(&p, arr, types);
	p.new[p.len] = 0;
	free_arr(arr);
	return (p.new);
}
