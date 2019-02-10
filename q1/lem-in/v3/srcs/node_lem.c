/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:47:57 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/09 21:01:58 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lem	g_lem;

void			init_lem(int verbose)
{
	g_lem.rooms = NULL;
	g_lem.paths = NULL;
	g_lem.ants = 0;
	g_lem.check = 0;
	g_lem.verbose = verbose;
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

static void		print_ants(int *pos, int index)
{
	int		i;
	int		offset;

	i = -1;
	offset = 0;
	while (++i < index)
		offset += g_lem.y[i];
	i = g_lem.x[index] - 1;
	while (i-- > 0)
		if (pos[i] > 0 && pos[i] <= g_lem.y[index])
		{
			ft_putstr("L");
			ft_putnbr(pos[i] + offset);
			ft_putchar('-');
			ft_putstr(g_lem.paths[index]->trail[i + 1]);
			ft_putchar(' ');
		}
}

void			move_ants(void)
{
	int		i;
	int		j;
	int		k;

	ft_putstr("\n   MOVING ANTS\n");
	if (!(g_lem.pos = (int**)ft_memalloc(sizeof(int*) * (g_lem.w))))
		exit_lem("Malloc fail moving ants 1\n");
	i = -1;
	while (++i < g_lem.w && (j = -1))
		if (!(g_lem.pos[i] = (int*)ft_memalloc(sizeof(int) * g_lem.x[i])))
			exit_lem("Malloc fail moving ants 2\n");
		else
			while (++j < g_lem.x[i])
				g_lem.pos[i][j] = -j;
	i = g_lem.x[0] + g_lem.y[0];
	while (--i && (j = -1))
	{
		while (++j < g_lem.w && (k = -1))
		{
			while (++k < g_lem.x[j])
				g_lem.pos[j][k]++;
			print_ants(g_lem.pos[j], j);
		}
		ft_putchar('\n');
	}
}
