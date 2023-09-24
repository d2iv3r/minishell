/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:48:48 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/09 19:11:10 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	print_env(t_env *env, int fd)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i].var)
	{
		if (env[i].value && ft_strcmp(env[i].var, "PATHY"))
		{
			ft_putstr_fd(env[i].var, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(env[i].value, fd);
		}
		i++;
	}
}

int	ft_env(char **args, t_env *env, int fd)
{
	if (!env)
		return (print_error("env: ", "not available!", 1, -1));
	if (args[1])
		return (print_error("env: ", "with no options or arguments!", 1, -1));
	print_env(env, fd);
	return (0);
}
