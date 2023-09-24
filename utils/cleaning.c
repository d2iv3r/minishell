/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:37 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 12:23:53 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	t_token	*tmp_token;

	tmp_cmd = cmds;
	while (cmds)
	{
		tmp_token = cmds->head_token;
		free(tmp_token->token_chars);
		while (tmp_token)
		{
			cmds->head_token = cmds->head_token->next;
			tmp_token = cmds->head_token;
		}
		tmp_cmd = tmp_cmd->next;
		free(cmds);
		cmds = cmds->next;
	}
}

void	free_fargs(t_fargs *fargs)
{
	int	i;

	i = 0;
	while (fargs[i].args)
	{
		free_arr(fargs[i].args);
		free_arr(fargs[i].rdrs);
		free(fargs[i].types2);
		free(fargs[i].types);
		i++;
	}
	free(fargs);
}

void	main_free_2(t_main_params *p)
{
	if (p->input)
	{
		free(p->input);
		p->input = NULL;
	}
	if (p->fargs)
	{
		free(p->fargs);
		p->fargs = NULL;
	}
	free_arr(p->splited_cmds);
	free_arr(p->expanded_values);
	while (p->commands)
	{
		p->cmd_head_holder = p->commands->next;
		free(p->commands);
		p->commands = NULL;
		p->commands = p->cmd_head_holder;
	}
}

void	main_free(t_main_params *p)
{
	p->i = 0;
	while (p->fargs[p->i].args)
	{
		if (p->fargs[p->i].args)
		{
			free_arr(p->fargs[p->i].args);
			p->fargs[p->i].args = NULL;
		}
		if (p->fargs[p->i].rdrs)
		{
			free_arr(p->fargs[p->i].rdrs);
			p->fargs[p->i].rdrs = NULL;
		}
		free(p->fargs[p->i].quoted);
		free(p->fargs[p->i].types);
		free(p->fargs[p->i].types2);
		p->i++;
	}
	main_free_2(p);
}
