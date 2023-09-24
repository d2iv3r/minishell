/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:01:39 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 12:23:43 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	len_tenv2(t_env *env)
{
	int	i;
	int	count;

	if (!env)
		return (0);
	i = 0;
	count = 0;
	while (env[i].var)
	{
		if (ft_strcmp(env[i].var, "OLDPWD") && ft_strcmp(env[i].var, "PATHY")
			&& ft_strcmp(env[i].var, "PWD") && ft_strcmp(env[i].var, "_"))
			count++;
		i++;
	}
	return (count);
}

char	**t_env_to_arr2d(t_env *env)
{
	char	**arr2d;
	int		i;
	int		len;
	int		j;

	len = len_tenv2(env);
	arr2d = malloc(sizeof(char *) * (len + 1));
	if (!arr2d)
		return (perror("Error: "), NULL);
	i = 0;
	j = 0;
	while (env[i].var && j < len)
	{
		if (ft_strcmp(env[i].var, "OLDPWD") && ft_strcmp(env[i].var, "PATHY")
			&& ft_strcmp(env[i].var, "PWD") && ft_strcmp(env[i].var, "_"))
		{
			arr2d[j] = ft_strjoin_2(ft_strdup(env[i].var), "=", 1);
			arr2d[j] = ft_strjoin_2(arr2d[j], ft_strdup(env[i].value), 2);
			j++;
		}
		i++;
	}
	arr2d[j] = NULL;
	return (arr2d);
}

int	print_error(char *args, char *err, int stat, int ret)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	g_status = stat;
	return (ret);
}

int	is_executable(char *arg, t_env *env)
{
	char	*cmd;
	char	*path;

	if (!arg)
		return (0);
	if (arg[0] && arg[1] && arg[0] == '.' && arg[1] == '/')
	{
		if (access(arg, F_OK) == 0 && access(arg, X_OK) == -1)
			return (print_error(arg, ": Permission denied", 126, 0), 0);
	}
	if (access(arg, X_OK) == 0)
		return (1);
	if (exist_var(env, "PATH") == -1 && exist_var(env, "PATHY") == -1)
		return (print_error(arg, ": No such file or directory", 127, 0), 0);
	if (exist_var(env, "PATH") == -1)
		path = env[exist_var(env, "PATHY")].value;
	else
		path = env[exist_var(env, "PATH")].value;
	cmd = get_access_path(path, arg);
	if (!cmd)
		return (print_error(arg, ": command not found", 127, 0), 0);
	return (free(cmd), 1);
}

void	wait_childs(int pid)
{
	if (pid != -1)
	{
		if (waitpid(pid, &g_status, 0) == -1)
			print_error("waitpid: ", strerror(errno), errno, -1);
		while (wait(0) != -1)
			;
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
		{
			g_status = WTERMSIG(g_status);
			if (g_status == SIGINT)
			{
				write(1, "\n", 1);
				g_status = 130;
			}
			else if (g_status == SIGQUIT)
			{
				ft_putendl_fd("Quit: 3", 1);
				g_status = 131;
			}
		}
	}
}
