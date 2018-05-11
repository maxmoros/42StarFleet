/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:54:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/11 10:29:33 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

long		free_map(t_map *map, long out)
{
	int		i;

	if (map)
	{
		if (map->xy)
		{
			i = -1;
			while (++i < map->dim[0])
				if (map->xy[i])
					free(map->xy[i]);
			free(map->xy);
		}
		free(map);
	}
	return (out);
}

static int			valid_line(char *map_line, int width)
{
	int		i;
	char	c;

	i = -1;
	while (++i < width)
	{
		c = map_line[i];
		if (c < '0' || c > '3')
			return (0);
	}
	return (1);
}

t_map		*new_map(int x, int y)
{
	t_map	*map;
	int		i;

	printf("Map Initializing\n");
	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->dim[0] = x;
	map->dim[1] = y;
	if (!(map->xy = (char**)ft_memalloc(sizeof(char*) * x)))
		return (NULL);
	i = -1;
	while (++i < y)
	{
		if (get_next_line(0, &map->xy[i]) < 1 ||
			(int)ft_strlen(map->xy[i]) != x || !valid_line(map->xy[i], x))
		{
			ft_putstr("Map Error\n");
			return ((t_map*)free_map(map, 0));
		}
	}
	printf("Map Initialized\n");
	return (map);
}

void		print_map(t_map *map)
{
	int		x;
	int		y;

	printf("Map Printing\n");
	y = -1;
	while (++y < map->dim[1])
	{
		x = -1;
		while (++x < map->dim[0])
			ft_putchar(map->xy[y][x]);
		ft_putchar('\n');
	}
}
