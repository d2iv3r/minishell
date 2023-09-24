/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:16:50 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 16:25:24 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		g_status = 16;
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status = 1;
	}
	if (sig == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			g_status = 131;
			return ;
		}
	}
}
