/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:06:44 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/14 13:44:55 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_new_line(char **arr2d, char *line)
{
	char	**new;
	int		i;

	if (!arr2d || !*arr2d)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (print_error("malloc", strerror(errno), errno, -1), NULL);
		new[0] = ft_strdup(line);
		new[1] = NULL;
		return (new);
	}
	new = malloc((sizeof(char *) * (len_arr2d(arr2d) + 2)));
	if (!new)
		return (print_error("malloc", strerror(errno), errno, -1), NULL);
	i = 0;
	while (arr2d[i])
	{
		new[i] = ft_strdup(arr2d[i]);
		i++;
	}
	new[i] = ft_strdup(line);
	new[i + 1] = NULL;
	clean_arr2d(arr2d);
	return (new);
}

int	ft_count_rdrs(t_token *start)
{
	t_token	*tmp;
	int		len;

	tmp = start;
	len = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->token_chars, ">>")
			|| !ft_strcmp(tmp->token_chars, ">")
			|| !ft_strcmp(tmp->token_chars, "<<")
			|| !ft_strcmp(tmp->token_chars,
				"<"))
		{
			len++;
			if (tmp->next)
			{
				len++;
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (len);
}

char	**get_herdoc_value(t_fargs *f_args, int *xpand)
{
	int		i;
	char	**buff;
	int		j;

	buff = NULL;
	i = -1;
	while (f_args[++i].args)
	{
		if (f_args[i].rdrs[0])
		{
			j = -1;
			while (f_args[i].rdrs[++j])
			{
				if (!ft_strcmp(f_args[i].rdrs[j], "<<") && j % 2 == 0)
				{
					clean_arr2d(buff);
					buff = NULL;
					read_lines(&buff, &f_args[i], j, xpand);
					if (f_args->sig_herdoc == 1)
						return (clean_arr2d(buff), NULL);
				}
			}
		}
	}
	return (buff);
}

void	check_max(char **rdrs)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (rdrs[i])
	{
		if (ft_strcmp(rdrs[i], "<<"))
			counter++;
		if (counter == 17)
		{
			printf("minishell: maximum here-document count exceeded");
			exit(2);
		}
		i++;
	}
}
