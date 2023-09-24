/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:39:45 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/15 17:07:41 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	get_fd_file(char *file_name, int io)
{
	int	fd;

	if (io == 0)
	{
		if (access(file_name, F_OK) == -1)
			return (print_error(file_name, ": No such file or directory",
					1, -1));
		else if (access(file_name, R_OK) == -1)
			return (print_error(file_name, ": Permission denied", 1, -1));
		fd = open(file_name, O_RDONLY);
	}
	if (io == 1 || io == 2)
	{
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) == -1)
			return (print_error(file_name, ": Permission denied", 1, -1));
		if (io == 1)
			fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (io == 2)
			fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	if (fd < 0)
		return (print_error("open: ", strerror(errno), errno, -1));
	return (fd);
}

int	get_herdoc_fd(t_fargs *fargs, char **herdoc)
{
	int			fd;
	int			i;
	static int	file;

	fargs->tmp_file = ft_strdup("/tmp/tmp_minishell");
	file = 0;
	while (access(fargs->tmp_file, F_OK) == 0)
		fargs->tmp_file = ft_strjoin_2(fargs->tmp_file, ft_itoa(++file), 2);
	fd = open (fargs->tmp_file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		return (print_error("open: ", strerror(errno), errno, -1));
	i = -1;
	if (herdoc)
	{
		while (herdoc[++i])
		{
			ft_putstr_fd(herdoc[i], fd);
			ft_putstr_fd("\n", fd);
		}
	}
	close(fd);
	fd = open(fargs->tmp_file, O_RDONLY);
	if (fd < 0)
		return (print_error("open: ", strerror(errno), errno, -1));
	return (fd);
}

void	redr_herdoc(t_fargs *fargs, int i, char **herdoc)
{
	if (fargs[i].infile != STDIN_FILENO)
		close(fargs[i].infile);
	if (fargs->tmp_file)
	{
		close(fargs[i].infile);
		unlink(fargs->tmp_file);
		free(fargs->tmp_file);
		fargs->tmp_file = NULL;
	}
	fargs[i].infile = get_herdoc_fd(fargs, herdoc);
}

int	get_infile(t_fargs *fargs, int i, char **herdoc)
{
	int	j;

	j = 0;
	fargs->tmp_file = NULL;
	while (fargs[i].rdrs[j])
	{
		if (j % 2 == 0)
		{
			if (!ft_strcmp(fargs[i].rdrs[j], "<<"))
				redr_herdoc(fargs, i, herdoc);
			else if (!ft_strcmp(fargs[i].rdrs[j], "<"))
			{
				if (fargs[i].infile != STDIN_FILENO)
					close(fargs[i].infile);
				fargs[i].infile = get_fd_file(fargs[i].rdrs[j + 1], 0);
			}
			if (fargs[i].infile == -1)
				return (-1);
		}
		j++;
	}
	if (fargs->tmp_file)
		free(fargs->tmp_file);
	return (0);
}

int	get_outfile(char **redr, int *outf)
{
	int	i;

	i = 0;
	while (redr[i])
	{
		if (i % 2 == 0)
		{
			if (!ft_strcmp(redr[i], ">>"))
			{
				if (*outf != STDOUT_FILENO)
					close(*outf);
				*outf = get_fd_file(redr[i + 1], 1);
			}
			else if (!ft_strcmp(redr[i], ">"))
			{
				if (*outf != STDOUT_FILENO)
					close(*outf);
				*outf = get_fd_file(redr[i + 1], 2);
			}
			if (*outf == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
