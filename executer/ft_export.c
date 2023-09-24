/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:37:20 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 22:17:29 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	print_export(t_env *env, int fd)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i].var)
	{
		if (ft_strcmp(env[i].var, "_") && ft_strcmp(env[i].var, "PATHY"))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env[i].var, fd);
			if (env[i].value)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(env[i].value, fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
}

int	valid_arg(char *arg)
{
	int	i;
	int	j;

	if (!arg)
		return (0);
	j = 0 ;
	if (!ft_isalpha(arg[j]) && ft_isdigit(arg[j]) && arg[j] != '_')
		return (print_error("export: ", "not a valid identifier", 1, 0), 0);
	while (arg[j] && arg[j] != '=')
		j++;
	if (arg[j - 1] == '+')
		j--;
	i = 0;
	while (i < j)
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (print_error("export: ", "not a valid identifier", 1, 0), 0);
		i++;
	}
	return (1);
}

void	update_env(t_env *env, char *arg)
{
	int	index;

	index = exist_var(env, arg);
	if (ft_strchr(arg, '+'))
		env[index].value = ft_strjoin_2(env[index].value, get_value(arg), 2);
	else
	{
		free(env[index].value);
		env[index].value = NULL;
		env[index].value = get_value(arg);
	}
}

t_env	*add_var(t_env *env, char *arg)
{
	int		i;
	t_env	*new_env;

	new_env = malloc(sizeof(t_env) * (len_tenv(env) + 2));
	if (!new_env)
	{
		return (print_error("malloc: ", strerror(errno), errno, -1), NULL);
		exit(1);
	}
	i = 0;
	if (env)
	{
		while (env[i].var)
		{
			new_env[i].var = ft_strdup(env[i].var);
			new_env[i].value = ft_strdup(env[i].value);
			i++;
		}
	}
	new_env[i].var = get_var(arg);
	new_env[i].value = get_value(arg);
	new_env[i + 1].var = NULL;
	new_env[i + 1].value = NULL;
	return (clean_env(env), new_env);
}

int	ft_export(t_fargs *f_args, t_env **env)
{
	int	i;

	if (!f_args->args[1])
	{
		print_export(*env, f_args->outfile);
		return (0);
	}
	i = 1;
	while (f_args->args[i])
	{
		if (valid_arg(f_args->args[i]))
		{
			if (exist_var(*env, f_args->args[i]) != -1
				&& ft_strcmp(f_args->args[i], "_"))
				update_env(*env, f_args->args[i]);
			else
				*env = add_var(*env, f_args->args[i]);
		}
		else
			return (-1);
		i++;
	}
	return (0);
}
