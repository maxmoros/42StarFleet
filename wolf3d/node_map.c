/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:54:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/29 18:28:55 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

long			free_map(t_map *map, long out)
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

static int		valid_line(char *map_line, int width)
{
	int		i;
	char	c;

	i = -1;
	while (++i < width)
	{
		c = map_line[i];
		if (c < '0' || c > '3')
		{
			ft_putstr("Invalid map line!\n");
			return (0);
		}
	}
	return (1);
}

static t_map	*init_map(int x, int y)
{
	t_map	*map;
	int		i;

	ft_putstr("\tMap Initializing\n");
	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))) ||
			!(map->xy = (char**)ft_memalloc(sizeof(char*) * x)))
		return ((t_map*)free_map(map, 0));
	map->dim[0] = x;
	map->dim[1] = y;
	i = -1;
	while (++i < x)
		if (!(map->xy[i] = (char*)ft_memalloc(sizeof(char) * y)))
			return ((t_map*)free_map(map, 0));
	ft_putstr("\t\tMap Initialized\n");
	return (map);
}

t_map			*new_map(int x, int y)
{
	t_map	*map;
	int		i;
	int		j;
	char	*line;

	if (!(map = init_map(x, y)))
		return (NULL);
	i = -1;
	ft_putstr("\t\tReading map\n");
	while (++i < y)
	{
		if ((j = get_next_line(0, &line)) < 1 ||
			(int)ft_strlen(line) != x || !valid_line(line, x))
		{
			ft_putstr("Map Error\n");
			j ? free(line) : NULL;
			return ((t_map*)free_map(map, 0));
		}
		j = -1;
		while (++j < x)
			map->xy[j][i] = line[j];
		free(line);
	}
	ft_putstr("\tMap successful\n");
	return (map);
}

void			print_map(t_map *map)
{
	int		x;
	int		y;

	ft_putstr("  Map Printing\n");
	y = -1;
	while (++y < map->dim[1])
	{
		x = -1;
		while (++x < map->dim[0])
			ft_putchar(map->xy[x][y]);
		ft_putchar('\n');
	}
	ft_putchar('\n');
}
