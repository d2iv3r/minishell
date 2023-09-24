/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:10 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 17:13:32 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_what_will_do_2(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{
	if (p->j > 0 && ft_strcmp(fargs[p->i].rdrs[p->j - 1], "<<"))
	{
		p->did_expand = 0;
		ft_what_will_do_while(p, fargs, expanded_value);
		fargs[p->i].rdrs[p->j] = ft_strdup(p->expanded);
	}
	else
	{
		fargs[p->i].rdrs[p->j] = ft_strdup(fargs[p->i].rdrs[p->j]);
		p->x += how_many_dollars(fargs[p->i].rdrs[p->j]);
	}
	p->j++;
}

void	while_1(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{
	while (p->j < p->args_len)
	{
		p->expanded = ft_strdup("");
		p->w = 0;
		ft_what_will_do_1(p, fargs, expanded_value);
	}
}

void	what_will_do_helper(t_fargs *fargs, char **expanded_value,
		t_params_5 *p)
{
	p->expanded = NULL;
	p->a_n_f_len = arr_len(fargs[p->i].rdrs);
	p->args_len = arr_len(fargs[p->i].args);
	p->j = 0;
	p->t = 0;
	p->holder = (char **)malloc(sizeof(char *)
			* (arr_len(fargs[p->i].args) + 1));
	if (!p->holder)
		exit(1);
	while (fargs[p->i].args[p->t])
	{
		p->holder[p->t] = fargs[p->i].args[p->t];
		p->t++;
	}
	p->holder[p->t] = 0;
	while_1(p, fargs, expanded_value);
	free_arr(p->holder);
	p->t = 0;
	p->holder = (char **)malloc(sizeof(char *)
			* (arr_len(fargs[p->i].rdrs) + 1));
	if (!p->holder)
		exit(1);
}

void	what_will_do_helper2(t_fargs *fargs, char **expanded_value,
		t_params_5 *p)
{
	while (p->t < p->a_n_f_len)
	{
		p->holder[p->t] = fargs[p->i].rdrs[p->t];
		p->t++;
	}
	p->holder[p->t] = 0;
	p->j = 0;
	while (p->j < p->a_n_f_len)
	{
		p->expanded = ft_strdup("");
		p->w = 0;
		ft_what_will_do_2(p, fargs, expanded_value);
		free(p->expanded);
	}
	free_arr(p->holder);
	p->i++;
}

int	ft_what_will_do(t_fargs *fargs, char **expanded_value)
{
	t_params_5	p;

	p.i = 0;
	p.x = 0;
	p.expanded = NULL;
	while (fargs[p.i].args)
	{
		what_will_do_helper(fargs, expanded_value, &p);
		what_will_do_helper2(fargs, expanded_value, &p);
	}
	p.i = 0;
	return (0);
}
