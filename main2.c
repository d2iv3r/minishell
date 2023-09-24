/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:13:34 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 22:14:11 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_intial_values(t_main_params *p, char **env)
{
	p->exp = NULL;
	p->fargs = NULL;
	p->commands = NULL;
	p->input = NULL;
	p->xxx = 0;
	p->env_2 = get_env(env);
	rl_catch_signals = 0;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}

void	main_while_inside_while(t_main_params *p)
{
	while (p->splited_cmds[p->i])
	{
		ft_addbackcmd(&p->commands, ft_newcmd("ignored_first"));
		while (p->commands->next)
			p->commands = p->commands->next;
		if (p->i == 0)
			p->cmd_head_holder = p->commands;
		p->commands->tokens = ft_make_tokens(p->splited_cmds[p->i]);
		p->j = 0;
		while (p->commands->tokens[p->j])
			ft_addback(&p->commands->head_token,
				make_tok0(p->commands->tokens[p->j++]));
		free(p->commands->tokens);
		p->j++;
		p->i++;
	}
}

void	main_inside_while(t_main_params *p)
{
	p->commands = NULL;
	p->expanded_values = (char **)malloc(sizeof(char *)
			* (how_many_dollars(p->input) + 1));
	if (!p->expanded_values)
		exit(1);
	p->expanded_values[0] = NULL;
	p->i = 0;
	while (p->splited_cmds[p->i])
	{
		ft_expand2(&p->splited_cmds[p->i], p->env_2, p->expanded_values, 1);
		p->i++;
	}
	p->i = 0;
	main_while_inside_while(p);
	p->i = 0;
	p->commands = p->cmd_head_holder;
	p->fargs = ft_argnew(p->commands);
	ft_what_will_do(p->fargs, p->expanded_values);
}
