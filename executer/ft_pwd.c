/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:33:27 by efarhat           #+#    #+#             */
/*   Updated: 2023/06/08 16:27:09 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (print_error("getcwd: ", strerror(errno), errno, -1));
	ft_putendl_fd(path, fd);
	free(path);
	return (0);
}
