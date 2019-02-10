/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:47:57 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/09 18:36:46 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lem	g_lem;

void			init_lem(void)
{
	g_lem.rooms = NULL;
	g_lem.paths = NULL;
	g_lem.ants = 0;
	g_lem.check = 0;
}

int				get_ants(void)
{
	char	*line;

	ft_putstr("\n   GETTING ANTS\n");
	if (get_next_line(0, &line) < 1)
		return (0);
	while (line[0] == '#' && line[1] != '#')
		if (get_next_line(1, &line) < 1)
			return (0);
	if (!ft_isint(line) || !ft_isalldig(line))
		return (0);
	g_lem.ants = ft_atoi(line);
	ft_putstr("Number of ants = ");
	ft_putnbr(g_lem.ants);
	ft_putstr("\n");
	free(line);
	return (g_lem.ants > 0 ? 1 : 0);
}

/*
static void		print_ants(int *pos)
{
	int		i;

	i = g_lem.paths->length;
	while (i-- > 0)
		if (pos[i] > 0 && pos[i] <= g_lem.ants)
		{
			ft_putstr("L");
			ft_putnbr(pos[i]);
			ft_putchar('-');
			ft_putstr(g_lem.path->path[i + 1]);
			if (i > 0 && pos[i - 1] <= g_lem.ants)
				ft_putchar(' ');
		}
	ft_putchar('\n');
}

void			move_ants(void)
{
	int		*pos;
	int		i;
	int		j;

	ft_putstr("\n   MOVING ANTS\n");
	if (!(pos = (int*)ft_memalloc(sizeof(int) * (g_lem.path->length))))
		return ;
	i = -1;
	while (++i < g_lem.path->length)
		pos[i] = -i;
	j = g_lem.path->length + g_lem.ants;
	while (--j)
	{
		i = -1;
		while (++i < g_lem.path->length)
			pos[i]++;
		print_ants(pos);
	}
	free(pos);
	ft_putstr("\n   COMPLETED\n");
}
*/
