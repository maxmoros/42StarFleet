/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tile_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:06 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:06 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "tile_type.h"

static int g_direction_vecs[][2] = {
	[NORTH] = { 0, -1 },
	[NORTHWEST] = { -1, -1 },
	[WEST] = { -1, 0 },
	[SOUTHWEST] = { -1, 1 },
	[SOUTH] = { 0, 1 },
	[SOUTHEAST] = { 1, 1 },
	[EAST] ={ 1, 0 },
	[NORTHEAST] = { 1, -1 }
};

t_tile	*get_tile_at_offset(t_tile *home, int dx, int dy)
{
	int tx;
	int ty;

	tx = (home->x + dx + g_map->dim.x) % g_map->dim.x;
	ty = (home->y + dy + g_map->dim.y) % g_map->dim.y;
	return (&g_map->tile[tx][ty]);
}

t_tile	*get_adj_tile(t_tile *home, int dir)
{
	int *vec;

	vec = g_direction_vecs[dir];
	return (get_tile_at_offset(home, vec[0], vec[1]));
}
