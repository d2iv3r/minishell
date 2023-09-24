/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:17:11 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/11 20:18:33 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	int		strlen;
	char	*str;

	if (!s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(strlen + 1);
	if (!str)
		return (0);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	return (str[i + ft_strlen(s1)] = 0, free(s1), str);
}

char	*ft_strjoin_2(char *s1, char *s2, int clean)
{
	char	*join;

	join = ft_strjoin_3(s1, s2);
	if (clean == 1)
		free(s1);
	if (clean == 2)
	{
		free(s1);
		free(s2);
	}
	return (join);
}

char	*ft_strjoin_3(char const *s1, char const *s2)
{
	size_t	i;
	int		strlen;
	char	*str;

	if (!s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(strlen + 1);
	if (!str)
		return (0);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	return (str[i + ft_strlen(s1)] = 0, str);
}
