/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:20:31 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/10 12:40:08 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	len_var(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] != '=' && line[i] != '+'))
		i++;
	return (i);
}

char	*get_value(char *line)
{
	int		i;
	char	*value;

	value = NULL;
	if (!line || !ft_strchr(line, '='))
		return (NULL);
	i = len_var(line);
	if (line[i] == '+')
		i++;
	if (line[i])
		value = ft_strdup(line + (i + 1));
	return (value);
}

char	*get_var(char *line)
{
	int		i;
	char	*var;
	int		len;

	if (!line)
		return (NULL);
	len = len_var(line);
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var[i] = line[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

t_env	*fill_tenv(char **env)
{
	t_env	*env_cpy;
	int		i;

	env_cpy = (t_env *)malloc(sizeof(t_env) * (len_arr2d(env) + 3));
	if (!env_cpy)
		return (ft_putstr_fd(strerror(errno), STDERR_FILENO), NULL);
	i = 0;
	if (env[i])
	{
		while (env[i])
		{
			env_cpy[i].var = get_var(env[i]);
			if (!ft_strcmp(env_cpy[i].var, "SHLVL"))
				env_cpy[i].value = add1_shlvl(get_value(env[i]));
			else
				env_cpy[i].value = get_value(env[i]);
			i++;
		}
	}
	env_cpy[i].var = ft_strdup("OLDPWD");
	env_cpy[i].value = NULL;
	env_cpy[++i].var = ft_strdup("PATHY");
	env_cpy[i].value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	return (env_cpy[++i].var = NULL, env_cpy[i].value = NULL, env_cpy);
}

t_env	*get_env(char **env)
{
	t_env	*env_cpy;
	char	*tmp;

	env_cpy = fill_tenv(env);
	if (!*env)
	{
		tmp = ft_strjoin_2(ft_strdup("PWD="), getcwd(NULL, 0), 2);
		env_cpy = add_var(env_cpy, tmp);
		free(tmp);
		env_cpy = add_var(env_cpy, "SHLVL=1");
		env_cpy = add_var(env_cpy, "_=/usr/bin/env");
		return (env_cpy);
	}
	if (exist_var(env_cpy, "PWD") == -1)
	{
		tmp = ft_strjoin_2(ft_strdup("PWD="), getcwd(NULL, 0), 2);
		env_cpy = add_var(env_cpy, tmp);
		free(tmp);
	}
	if (exist_var(env_cpy, "SHLVL") == -1)
		env_cpy = add_var(env_cpy, "SHLVL=1");
	if (exist_var(env_cpy, "_") == -1)
		env_cpy = add_var(env_cpy, "_=/bin/usr/env");
	return (env_cpy);
}
