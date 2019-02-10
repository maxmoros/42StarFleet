/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:07 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:07 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "tile_type.h"

#define DEFAULT_PARRAY 8

int				init_tile(t_tile *t, int x, int y)
{
	int			i;

	i = -1;
	t->x = x;
	t->y = y;
	if ((t->players = malloc(sizeof(t_player *) * DEFAULT_PARRAY)) == NULL)
		ERR_OUT("init_tile; malloc");
	t->parray_size = DEFAULT_PARRAY;
	bzero(t->players, sizeof(t_player *) * t->parray_size);
	t->count[PLAYERS] = 0;
	while (++i < 6)
		t->count[i] = 0;
	t->count[FOOD] = 0;
	t->eggs = 0;
	bzero(t->count, sizeof(t->count));
	return (0);
}

int				create_map(int x, int y)
{
	int			i;
	int			k;

	i = -1;
	g_map->dim.x = x;
	g_map->dim.y = y;
	if ((g_map->tile = malloc(x * sizeof(t_tile *))) == NULL)
		ERR_OUT("map_creation; malloc");
	while (++i < x)
		if ((g_map->tile[i] = malloc(y * sizeof(t_tile))) == NULL)
			ERR_OUT("map_creation; malloc");
	i = -1;
	k = -1;
	while (++i < x)
	{
		while (++k < y)
			init_tile(&g_map->tile[i][k], i, k);
		k = -1;
	}
	return (0);
}
