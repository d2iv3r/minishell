/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:36:26 by efarhat           #+#    #+#             */
/*   Updated: 2022/11/08 11:42:52 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(long nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
		nb = nb * -1;
	}
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	len;
	long	l;

	l = n;
	len = ft_numlen(l);
	p = malloc(sizeof(char) * len + 1);
	if (p == NULL)
		return (NULL);
	if (l == 0)
		p[0] = 48;
	if (l < 0)
	{
		p[0] = '-';
		l = l * -1;
	}
	p[len] = '\0';
	len--;
	while (l > 0)
	{
		p[len] = (l % 10) + 48;
		l /= 10;
		len--;
	}
	return (p);
}
