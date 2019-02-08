/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:44:47 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/05 17:54:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				free_ret(char *line, int ret)
{
	free(line);
	return (ret);
}

static t_path	*new_path(int length)
{
	t_path	*node;

	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	if (!(node->trail = (char**)ft_memalloc(sizeof(char*) * (length + 2))))
		return (NULL);
	node->trail[length + 1] = NULL;
	node->length = length;
	return (node);
}

static void		backtrack(t_path *path)
{
	int		room_num;
	int		door_num;
	int		step;

	step = path->length;
	room_num = g_lem.room_count - 1;
	path->trail[step] = get_room(room_num)->name;
	while (room_num)
	{
		door_num = -1;
		while (g_lem.map[room_num][++door_num] != step)
			;
//		g_lem.map[room_num][door_num] = -3;
		path->trail[--step] = get_room(door_num)->name;
		room_num = door_num;
	}
}

static void		print_path(t_path *path)
{
	char	**trail;

	trail = path->trail;
	ft_putstr("\n   _PATH\n");
	while (*trail)
	{
		ft_putstr(*trail++);
		if (*trail)
			ft_putstr("->");
	}
	ft_putstr("\n");
}

int				*path_options(int path_count)
{
	int		*x;
	int		*raw;
	int		i;

	if (!(x = (int*)ft_memalloc(sizeof(int) * path_count)))
		return (NULL);
	i = -1;
	raw = g_lem.map[g_lem.room_count - 1];
	while (++i < path_count)
	{
		while (*raw < 1)
			raw++;
		x[i] = *raw++;
	}
	ft_qsort(x, path_count);
	return (x);
}

int				num_paths_touse(int path_count)
{
	int		w;
	int		s;

	w = 0;
	s = 0;
	while (s < g_lem.ants && ++w < path_count)
		s += (g_lem.x[w] - g_lem.x[w - 1]) * w;
	if (!(g_lem.y = (int*)ft_memalloc(sizeof(int) * w)))
		return (0);
	if (!(g_lem.paths = (t_path**)ft_memalloc(sizeof(t_path*) * (w + 1))))
		return (0);
	g_lem.paths[w] = NULL;
	return (w);
}

void			ants_per_path(void)
{
	int		n;
	int		i;

	n = g_lem.ants;
	while (n--)
	{
		i = g_lem.w - 1;
		while (i > 0 &&
				(g_lem.x[i] + g_lem.y[i]) >= (g_lem.x[i - 1] + g_lem.y[i - 1]))
			i--;
		ft_putnbr(i);//##########
		ft_putstr(", ");//#######
		g_lem.y[i]++;
	}
		ft_putstr("\n");
}

void			print_list(int *list, int num)
{
	ft_putstr("[");
	while (num--)
	{
		ft_putnbr(*list++);
		if (num)
			ft_putstr(", ");
	}
	ft_putstr("]\n");
}

void			build_paths(void)
{
	int		i;

	i = -1;
	while (++i < g_lem.w)
	{
		g_lem.paths[i] = new_path(g_lem.x[i]);
		backtrack(g_lem.paths[i]);
		print_path(g_lem.paths[i]);
	}
}

void			map_path(void)
{
	int		i;
	int		path_count;

	path_count = 0;
	i = -1;
	while (++i < g_lem.room_count)
		if (g_lem.map[g_lem.room_count - 1][i] > 0)
			path_count++;
	g_lem.x = path_options(path_count);
	print_list(g_lem.x, path_count);
	g_lem.w = num_paths_touse(path_count);
	ants_per_path();
	print_list(g_lem.x, g_lem.w);
	print_list(g_lem.y, g_lem.w);
	build_paths();


	/*
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
	*/
}
