/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:17:04 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 22:17:47 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_builtins(t_fargs *f_args, int i, t_env **env, int builtins_no)
{
	int	ret;

	if (exist_var(*env, "PATH") == -1 && exist_var(*env, "PATHY") == -1
		&& is_builtins(f_args[i].args) == ENV)
		return (print_error(f_args[i].args[0], ": No file or dir", 127, 0));
	ret = 0;
	if (builtins_no == ECHO)
		ret = ft_echo(f_args[i].args, f_args[i].outfile);
	else if (builtins_no == CD)
		ret = ft_cd(f_args[i].args, env);
	else if (builtins_no == PWD)
		ret = ft_pwd(f_args[i].outfile);
	else if (builtins_no == EXPORT)
		ret = ft_export(&f_args[i], env);
	else if (builtins_no == UNSET)
		ret = ft_unset(&f_args[i], env);
	else if (builtins_no == ENV)
		ret = ft_env(f_args[i].args, *env, f_args->outfile);
	else if (builtins_no == EXIT)
		ft_exit(f_args[i].args);
	if (f_args[i].infile != STDIN_FILENO)
		close(f_args[i].infile);
	if (f_args->outfile != STDOUT_FILENO)
		close(f_args[i].outfile);
	return (ret);
}
