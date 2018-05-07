/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:54:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/06 20:31:53 by mmoros           ###   ########.fr       */
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

t_map		*new_map(int x, int y)
{
	t_map	*map;
	int		i;

	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->dim[0] = x;
	map->dim[1] = y;
	if (!(map->xy = (char**)ft_memalloc(sizeof(char*) * x)))
		return (NULL);
	i = -1;
	while (++i < y)
	{
		if (get_next_line(0, &map->xy[i]) < 1)
			return ((t_map*)free_map(map, 0));
	}
	return (map);
}

void		print_map(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->dim[1])
	{
		x = -1;
		while (++x < map->dim[0])
			ft_putchar(map->xy[x][y]);
	}
}