/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:41:51 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 15:42:18 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	open_close(t_fargs *f_args, int i, int oc)
{
	int	fd[2];

	if (oc == OPEN_PIPE)
	{
		if (pipe(fd) == -1)
			return (print_error("pipe: ", strerror(errno), errno, -1));
		f_args[i + 1].infile = fd[0];
		f_args[i].outfile = fd[1];
	}
	else
	{
		if (f_args[i].outfile != STDOUT_FILENO)
			close(f_args[i].outfile);
		if (f_args[i].infile != STDIN_FILENO)
			close(f_args[i].infile);
		if (oc == CLOSE_CH)
		{
			if (f_args->sig_herdoc == 2 && f_args[i].infile != STDIN_FILENO)
				close (f_args[i].infile);
			if (f_args[i + 1].args)
				close(f_args[i + 1].infile);
		}
	}
	return (0);
}
