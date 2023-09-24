/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:54:24 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/12 12:56:55 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	clean_arr2d(char **arr2d)
{
	int	i;

	if (!arr2d || !*arr2d)
		return ;
	i = 0;
	while (arr2d[i])
	{
		free(arr2d[i]);
		arr2d[i] = NULL;
		i++;
	}
	free(arr2d);
	arr2d = NULL;
}

void	clean_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i].var)
	{
		free(env[i].var);
		env[i].var = NULL;
		free(env[i].value);
		env[i].value = NULL;
		i++;
	}
	free(env);
	env = NULL;
}
