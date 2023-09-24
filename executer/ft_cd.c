/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:25:09 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/12 16:18:55 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	update_pwd(t_env *env)
{
	int		index;
	char	*old_pwd;

	index = exist_var(env, "PWD=");
	if (index == -1)
		return ;
	old_pwd = ft_strdup(env[index].value);
	free(env[index].value);
	env[index].value = NULL;
	env[index].value = getcwd(NULL, 0);
	index = exist_var(env, "OLDPWD=");
	free(env[index].value);
	env[index].value = NULL;
	env[index].value = old_pwd;
}

int	ft_cd_tilde(char **arg)
{
	char	*tmp;

	tmp = ft_strdup(getenv("HOME"));
	if (arg[1][1])
		tmp = ft_strjoin_2(tmp, (arg[1] + 1), 1);
	if (chdir(tmp) != 0)
		return (print_error("chdir: ", strerror(errno), 1, -1));
	free(tmp);
	return (0);
}

int	ft_cd(char **arg, t_env **env)
{
	if (!arg[1])
	{
		if (exist_var(*env, "HOME") == -1)
			return (print_error("cd: ", "HOME not set", 1, -1));
		else
		{
			if (chdir(getenv("HOME")) != 0)
				return (print_error("cd: ", strerror(errno), 1, -1));
		}
	}
	else if (arg[1][0] == '~')
	{
		if (ft_cd_tilde(arg) != 0)
			return (-1);
	}
	else
	{
		if (chdir(arg[1]) != 0)
			return (print_error("chdir: ", strerror(errno), 1, -1));
	}
	update_pwd(*env);
	return (0);
}
