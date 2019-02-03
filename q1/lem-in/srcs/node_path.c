/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:44:47 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/02 19:01:14 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*new_path(int length)
{
	t_path	*node;

	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	if (!(node->path = (char**)ft_memalloc(sizeof(char*) * (length + 2))))
		return (NULL);
	node->path[length + 1] = NULL;
	node->length = length;
	return (node);
}

int				free_ret(char *line, int ret)
{
	free(line);
	return (ret);
}

static void		backtrack(void)
{
	int		room_num;
	int		door_num;
	int		step;

	step = g_lem.path->length;
	room_num = g_lem.room_count - 1;
	g_lem.path->path[step] = get_room(room_num)->name;
	while (room_num)
	{
		door_num = -1;
		while (g_lem.map[room_num][++door_num] != step)
			;
		g_lem.path->path[--step] = get_room(door_num)->name;
		room_num = door_num;
	}
}

static void		print_path(void)
{
	char	**path;

	path = g_lem.path->path;
	ft_putstr("\n   SHORTEST PATH\n");
	while (*path)
	{
		ft_putstr(*path++);
		if (*path)
			ft_putstr("->");
	}
	ft_putstr("\n");
}

void			map_path(void)
{
	int		min_length;
	int		i;

	min_length = g_lem.room_count;
	i = -1;
	while (++i < g_lem.room_count)
		if (g_lem.map[g_lem.room_count - 1][i] > 0 &&
				g_lem.map[g_lem.room_count - 1][i] < min_length)
			min_length = g_lem.map[g_lem.room_count - 1][i];
	g_lem.path = new_path(min_length);
	backtrack();
	print_path();
}
