/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:39:44 by ytoumi            #+#    #+#             */
/*   Updated: 2023/06/15 13:11:44 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_while(t_params_8 *p, char **buff)
{
	while (buff[p->i][p->z])
	{
		if (buff[p->i][p->z] == '$' && (buff[p->i][p->z]
				&& (ft_isalnum(buff[p->i][p->z + 1]) || buff[p->i][p->z
					+ 1] == '_')))
		{
			p->j = 0;
			while (p->j < p->her_values[p->t][p->j])
			{
				p->holder[p->x] = p->her_values[p->t][p->j];
				p->x++;
				p->j++;
			}
			p->z++;
			p->t++;
			while (ft_isalnum(buff[p->i][p->z]))
				p->z++;
		}
		else
		{
			p->holder[p->x] = buff[p->i][p->z];
			p->z++;
			p->x++;
		}
	}
}

void	herdoc_01(t_params_8 *p, t_env *env_2, char **buff)
{
	while (buff[p->i])
	{
		p->len += how_many_dollars(buff[p->i]);
		p->i++;
	}
	if (p->len)
	{
		p->her_values = (char **)malloc(sizeof(char *) * (p->len + 1));
		p->her_values[0] = 0;
	}
	else
		p->her_values = NULL;
	p->i = 0;
	while (buff[p->i])
	{
		ft_expand2(&buff[p->i], env_2, p->her_values, 0);
		p->i++;
	}
}

char	**exp_herdoc_value(char **buff, t_env *env_2)
{
	t_params_8	p;

	p.i = 0;
	p.x = 0;
	p.j = 0;
	p.t = 0;
	p.len = 0;
	herdoc_01(&p, env_2, buff);
	p.expanded_her = (char **)malloc(sizeof(char *) * (arr_len(buff) + 1));
	p.i = 0;
	while (buff[p.i])
	{
		p.x = 0;
		p.z = 0;
		herdoc_while(&p, buff);
		p.holder[p.x] = 0;
		p.expanded_her[p.i] = ft_strdup(p.holder);
		p.i++;
	}
	p.expanded_her[p.i] = 0;
	free_arr(buff);
	free_arr(p.her_values);
	return (p.expanded_her);
}

void	while_read_lines(char ***buff, t_fargs *fargs, int j, char *line)
{
	while (1)
	{
		signal(SIGINT, sig_herdoc);
		line = readline(">");
		if (g_status == 16)
		{
			clean_arr2d(*buff);
			fargs->sig_herdoc = 1;
			g_status = 1;
			break ;
		}
		if (!line)
		{
			fargs->sig_herdoc = 2;
			break ;
		}
		if (!ft_strcmp(fargs->rdrs[j + 1], line))
		{
			free(line);
			fargs->sig_herdoc = 3;
			break ;
		}
		*buff = add_new_line(*buff, line);
		free(line);
	}
}

void	read_lines(char ***buff, t_fargs *fargs, int j, int *xpand)
{
	char	*line;

	if (fargs->quoted[j + 1] == 0)
		*xpand = 1;
	line = NULL;
	fargs->incpy = dup(STDIN_FILENO);
	fargs->tmp_file = NULL;
	while_read_lines(buff, fargs, j, line);
	if (fargs->sig_herdoc != 1)
		close (fargs->incpy);
	signal(SIGINT, sig_handler);
}
