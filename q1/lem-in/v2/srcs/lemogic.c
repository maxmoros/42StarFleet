/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemogic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:45:25 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/05 17:47:20 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				build_logic_map(void)
{
	int		**map;
	t_room	*room;
	int		i;
	int		j;

	if (!(map = (int**)ft_memalloc(sizeof(int*) * g_lem.room_count)))
		return (0);
	i = -1;
	room = g_lem.rooms;
	while (room && ++i < g_lem.room_count)
	{
		if (!(map[i] = (int*)ft_memalloc(sizeof(int) * g_lem.room_count)))
			return (0);
		j = -1;
		while (++j < g_lem.room_count)
			if (room->adjc[j])
				map[i][j] = -1;
		room = room->next;
	}
	g_lem.map = map;
	return (1);
}

static void		recurse_map(int prev_room_num, int room_num, int step)
{
	int		i;

	g_lem.map[room_num][prev_room_num] = step;
	if (room_num == g_lem.room_count - 1)
		return ;
	i = -1;
	while (++i < g_lem.room_count)
		if (g_lem.map[room_num][i] == -1)
		{
			g_lem.map[room_num][i] = -2;
			recurse_map(room_num, i, step + 1);
		}
}

static void		set_colour(int step, char exit)
{
	ft_putstr("\x1b[3");
	ft_putnbr(step % 8);
	ft_putstr(";1m");
	if (exit)
		ft_putnbr(step);
	else
		ft_putchar('x');
	ft_putstr("\x1b[0m");
}

static void		print_logicmap(void)
{
	int		i;
	int		j;

	ft_putstr("    LOGIC MAP\n");
	i = -1;
	while (++i < g_lem.room_count)
	{
		j = -1;
		ft_putstr(get_room(i)->name);
		ft_putstr("\t: ");
		while (++j < g_lem.room_count)
			if (g_lem.map[i][j] == 0)
				ft_putchar('#');
			else if (g_lem.map[i][j] == -1)
				ft_putchar('.');
			else if (g_lem.map[i][j] == -2)
				set_colour(g_lem.map[j][i], 0);
			else
				set_colour(g_lem.map[i][j], 1);
		ft_putchar('\n');
	}
}

int				traverse_map(void)
{
	int		i;

	recurse_map(0, 0, 0);
	print_logicmap();
	i = -1;
	while (++i < g_lem.room_count)
		if (g_lem.map[g_lem.room_count - 1][i] > 0)
			return (1);
	return (0);
}
