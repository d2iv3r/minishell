/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:19:55 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/11 16:44:56 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	get_index(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!args[i])
		return (1);
	while (args[i])
	{
		if ((args[i][j] && args[i][j + 1])
			&& (args[i][j] == '-' && args[i][j + 1] == 'n'))
		{
			j++;
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (!args[i][j])
				i++;
			else
				break ;
			j = 0;
		}
		else
			break ;
	}
	return (i);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	n;

	i = get_index(args);
	if (i > 1)
		n = 1;
	else
		n = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
		if (args[i])
			ft_putstr_fd(" ", fd);
	}
	if (n == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
