/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:46:26 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/12 14:38:34 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	len_tenv(t_env	*env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i].var)
		i++;
	return (i);
}

int	len_arr2d(char **arr2d)
{
	int	i;

	if (!arr2d || !*arr2d)
		return (0);
	i = 0;
	while (arr2d[i])
		i++;
	return (i);
}

int	exist_var(t_env *env, char *arg)
{
	int		i;
	char	*var;

	var = get_var(arg);
	i = 0;
	while (env[i].var)
	{
		if (!ft_strcmp(env[i].var, var))
			return (free(var), i);
		i++;
	}
	free (var);
	var = NULL;
	return (-1);
}

char	*add1_shlvl(char *value)
{
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(value) + 1);
	free(value);
	return (shlvl);
}

char	*get_access_path(char *path, char *arg)
{
	int		i;
	char	*exe;
	char	**paths;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin_2(paths[i], ft_strjoin_3("/", arg), 2);
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			exe = ft_strdup(paths[i]);
			return (clean_arr2d(paths), exe);
		}
		i++;
	}
	return (clean_arr2d(paths), NULL);
}
