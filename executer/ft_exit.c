/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:02:28 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/12 18:21:10 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

long long	ft_atoi_long(char *str)
{
	int			i;
	int			s;
	long long	nb;

	i = 0;
	s = 1;
	nb = 0;
	while ((str[i] != '\0') && ((str[i] == 32) || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - 48);
		if (nb > 9223372036854775807 && s == 1)
			return (-1);
		if (nb > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return (nb * s);
}

int	is_all_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		g_status = 0;
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(args[1]) > 20 || !is_all_digit(args[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		print_error(args[1], ": numeric argument required", 255, 1);
		g_status = 255;
		exit(EXIT_FAILURE);
	}
	else if (args[2])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		print_error("exit: ", "too many arguments", 1, -1);
		g_status = 1;
		return ;
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	g_status = ft_atoi_long(args[1]);
	exit(ft_atoi_long(args[1]));
}
