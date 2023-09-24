/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:37 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/14 21:47:37 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	len_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].var)
		i++;
	return (i);
}

t_env	*remove_var(t_env *env, int index)
{
	int		i;
	t_env	*new_env;

	if (index == -1)
		return (env);
	new_env = malloc(sizeof(t_env) * len_env(env));
	if (!new_env)
		return (ft_putstr_fd(strerror(errno), STDERR_FILENO), NULL);
	i = 0;
	while (i != index)
	{
		new_env[i].var = ft_strdup(env[i].var);
		new_env[i].value = ft_strdup(env[i].value);
		i++;
	}
	while (i < len_env(env) - 1)
	{
		new_env[i].var = ft_strdup(env[i + 1].var);
		new_env[i].value = ft_strdup(env[i + 1].value);
		i++;
	}
	new_env[i].var = NULL;
	new_env[i].value = NULL;
	clean_env(env);
	return (new_env);
}

int	ft_unset(t_fargs *f_args, t_env **env)
{
	int	i;

	if (!f_args->args[1])
		return (0);
	i = 1;
	while (f_args->args[i])
	{
		if (!ft_strcmp(f_args->args[i], "PATH"))
		{
			*env = remove_var(*env, exist_var(*env, "PATHY"));
			*env = remove_var(*env, exist_var(*env, "PATH"));
		}
		if (exist_var(*env, f_args->args[i]) != -1
			&& ft_strcmp(f_args->args[i], "_"))
		{
			*env = remove_var(*env, exist_var(*env, f_args->args[i]));
		}
		i++;
	}
	return (0);
}
