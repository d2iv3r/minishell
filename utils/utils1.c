/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:00 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 20:22:28 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	len_till_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	return (i);
}

int	how_many_dollars(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '$')
			x++;
		i++;
	}
	return (x);
}

void	append_to_value_arr(char **arr, char *new_value)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	arr[i++] = new_value;
	arr[i] = 0;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
		}
		arr[i] = 0;
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}
