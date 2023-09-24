/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:21:03 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 22:32:55 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*g_exe(char *arg, t_env *env)
{
	char	*path;
	char	*cmd;

	if (access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	if (exist_var(env, "PATH") == -1)
		path = env[exist_var(env, "PATHY")].value;
	else
		path = env[exist_var(env, "PATH")].value;
	cmd = get_access_path(path, arg);
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	set_io_files(t_fargs *f_args, int i, char **herdoc)
{
	if (i == 0)
		f_args[i].infile = STDIN_FILENO;
	if (f_args[i + 1].args)
	{
		if (open_close(f_args, i, OPEN_PIPE) == -1)
			return (-1);
	}
	else
		f_args[i].outfile = STDOUT_FILENO;
	if (f_args[i].rdrs[0])
	{
		if (get_infile(f_args, i, herdoc) == -1)
		{
			if (f_args[i + 1].args)
				close(f_args[i].outfile);
			return (-1);
		}
		if (get_outfile(f_args[i].rdrs, &f_args[i].outfile) == -1)
		{
			if (f_args[i + 1].args)
				close(f_args[i].outfile);
			return (-1);
		}
	}
	return (0);
}

int	exec_cmd(t_fargs *f_args, int i, t_env *env, char *cmd)
{
	int			pid;
	char		**envv;

	envv = t_env_to_arr2d(env);
	pid = fork();
	if (pid == -1)
		return (free(cmd), clean_env(env), clean_arr2d(envv),
			print_error("fork: ", strerror(errno), errno, 1), -1);
	if (pid == 0)
	{
		if (dup2(f_args[i].outfile, STDOUT_FILENO) == -1)
			return (print_error("dup2: ", strerror(errno), errno, 1), -1);
		if (dup2(f_args[i].infile, STDIN_FILENO) == -1)
			return (print_error("dup2: ", strerror(errno), errno, 1), -1);
		open_close(f_args, i, CLOSE_CH);
		if (execve(cmd, f_args[i].args, envv) == -1)
			print_error("execve: ", strerror(errno), errno, 1);
	}
	if (cmd)
		free (cmd);
	open_close(f_args, i, CLOSE_P);
	return (clean_arr2d(envv), pid);
}

int	is_builtins(char **cmd)
{
	if (!*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (CD);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd[0], "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd[0], "env"))
		return (ENV);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (EXIT);
	return (0);
}

void	ft_execute(t_fargs *f_args, t_env **env, char **herdoc)
{
	int		i;
	int		pid;

	i = 0;
	pid = -1;
	while (f_args[i].args)
	{
		if (is_builtins(f_args[i].args))
		{
			if (set_io_files(f_args, i, herdoc) == 0 && !ft_builtins(
					f_args, i, env, is_builtins(f_args[i].args)))
				g_status = 0;
		}
		else if (is_executable(f_args[i].args[0], *env))
		{
			if (set_io_files(f_args, i, herdoc) == 0)
			{
				pid = exec_cmd(f_args, i, *env, g_exe(f_args[i].args[0], *env));
				if (pid == -1)
					break ;
			}
		}
		i++;
	}
	wait_childs(pid);
}

// void	ft_execute(t_fargs *f_args, t_env **env, char **herdoc)
// {
// 	int		i;
// 	int		pid;
// 	int		x;

// 	i = 0;
// 	pid = -1;
// 	while (f_args[i].args)
// 	{
// 		if (is_builtins(f_args[i].args))
// 		{
// 			if (exist_var(*env, "PATH") == -1 && exist_var(*env, "PATHY") == -1
// 				&& is_builtins(f_args[i].args) == ENV)
// 			{
// 				print_error(f_args[i].args[0], ":
// No such file or directory", 127, 0);
// 				i++;
// 				continue ;
// 			}
// 			x = set_io_files(f_args, i , herdoc);
// 			if (x == -1 && f_args[i + 1].args)
// 			{
// 				close(f_args[i].outfile);
// 				i++;
// 				continue ;
// 			}
// 			if (x == -1)
// 				return ;
// 			if (ft_builtins(f_args, i, env, is_builtins(f_args[i].args)) == -1)
// 				return ;
// 			g_status = 0;
// 		}
// 		else if (is_executable(f_args[i].args[0], *env))
// 		{
// 			x = set_io_files(f_args, i , herdoc);
// 			if (x == -1 && f_args[i + 1].args)
// 			{
// 				close(f_args[i].outfile);
// 				i++;
// 				continue ;
// 			}
// 			if (x == -1)
// 				return ;
// 			pid = exec_command(f_args, i, *env, g_exe(f_args[i].args[0], *env));
// 			if (pid == -1)
// 				return ;
// 		}
// 		i++;
// 	}
// 	wait_childs(pid);
// }
