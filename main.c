/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:09:01 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 22:40:06 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_inside_while_while(t_main_params *p)
{
	while (p->fargs[p->i].args)
	{
		if (p->fargs[p->i].args[0])
			p->fargs[p->i].args = do_split(p->fargs[p->i].args,
					p->fargs[p->i].types);
		if (p->fargs[p->i].rdrs[0])
			p->fargs[p->i].rdrs = do_split(p->fargs[p->i].rdrs,
					p->fargs[p->i].types2);
		p->i++;
	}
}

int	main_inside_while_2(t_main_params *p)
{
	int	xpand;

	p->i = 0;
	ft_quotes_removal(p->fargs);
	p->i = 0;
	main_inside_while_while(p);
	p->fargs->sig_herdoc = 0;
	xpand = 0;
	p->herdoc = get_herdoc_value(p->fargs, &xpand);
	if (!p->herdoc && p->fargs->sig_herdoc == 1)
	{
		if (p->fargs->sig_herdoc == 1)
			dup2(p->fargs->incpy, STDIN_FILENO);
		return (close(p->fargs->incpy), 1);
	}
	if (p->fargs->sig_herdoc == 2 && !p->fargs[0].args[0])
		return (clean_arr2d(p->herdoc), 1);
	if (xpand == 1 && p->herdoc)
		p->herdoc = exp_herdoc_value(p->herdoc, p->env_2);
	ft_execute(p->fargs, &p->env_2, p->herdoc);
	clean_arr2d(p->herdoc);
	unlink(p->fargs->tmp_file);
	p->i = 0;
	return (0);
}

int	inside_main(t_main_params *p)
{
	if (ft_strlen(p->input))
	{
		add_history(p->input);
		p->i = 0;
		if (check_pipes(p->input))
			return (1);
		replace_char(p->input, '|', 11);
		p->splited_cmds = ft_split(p->input, 11);
		if (ft_quotes(p->splited_cmds))
		{
			return (1);
		}
		main_inside_while(p);
		check_max(p->fargs->rdrs);
		if (ft_check_rdr(p->fargs))
			return (2);
		if (main_inside_while_2(p))
		{
			return (2);
		}
		main_free(p);
	}
	return (0);
}

void	main_x(t_main_params *p)
{
	p->input = readline("-> minishell$> ");
	if (!p->input)
	{
		printf("exit\n");
		exit(0);
	}
	p->input_holder = p->input;
	p->input = ft_strtrim(p->input);
	free(p->input_holder);
	p->xxx = inside_main(p);
}

int	main(int c, char **v, char **env)
{
	t_main_params	p;

	(void)v;
	if (c != 1)
		return (0);
	main_intial_values(&p, env);
	while (1)
	{
		main_x(&p);
		if (p.input)
		{
			free(p.input);
			p.input = NULL;
		}
		if (p.xxx)
		{
			if (p.xxx == 2)
				main_free(&p);
			continue ;
		}
	}
}
