/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:40:04 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 17:10:23 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_to_arr(char ***arr, char *new_value)
{
	int		i;
	char	**new;
	char	**arr_holder;

	new = (char **)malloc(sizeof(char *) * (arr_len(*arr) + 2));
	if (!new)
		exit(1);
	arr_holder = *arr;
	i = 0;
	while (i < arr_len(arr_holder))
	{
		new[i] = ft_strdup(arr_holder[i]);
		i++;
	}
	new[i] = ft_strdup(new_value);
	i++;
	new[i] = 0;
	*arr = new;
	free_arr(arr_holder);
	free(new_value);
	return (new);
}

int	rdr_while(t_fargs *fargs, int len, int i, int j)
{
	while (j < len)
	{
		if (fargs[i].types2[j] == 1 && fargs[i].types2[j - 1] == 1)
		{
			printf("parse error near '%s'\n", fargs[i].rdrs[j + 1]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	ambiguos(char **rdrs)
{
	int	i;

	i = 0;
	while (rdrs[i])
	{
		if (!ft_strlen(rdrs[i + 1]))
		{
			printf("ambiguuous redirect\n");
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	ft_check_rdr(t_fargs *fargs)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (fargs[++i].args)
	{
		len = arr_len(fargs[i].rdrs);
		if (!len)
		{
			continue ;
		}
		if (len && fargs[i].types2[len - 1] == 1)
		{
			printf("parse error near '\\n'\n");
			return (g_status = 258, 1);
		}
		j = 1;
		if (rdr_while(fargs, len, i, j))
			return (g_status = 258, 1);
		if (ambiguos(fargs[i].rdrs))
			return (g_status = 1, 1);
	}
	return (0);
}

char	*add_char(char *str, char c)
{
	int		i;
	char	*new;

	new = (char *)malloc(ft_strlen(str) + 2);
	if (!new)
		exit(1);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}
