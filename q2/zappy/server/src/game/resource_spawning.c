/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_spawning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:59 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:59 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "tile_type.h"

#define LINEMATE_CHANCE 9
#define DERAUMERE_CHANCE 8
#define SIBUR_CHANCE 10
#define MENDIANE_CHANCE 5
#define PHIRAS_CHANCE 6
#define THYSTAME_CHANCE 1
#define FOOD_CHANCE 28
#define SPAWN_CHANCE_NUMERATOR 1
#define SPAWN_CHANCE_DENOMINATOR 600
#define PREGAME_RESOURCE_SPAWNING_ROUNDS 1000

static int	sum_resource_chances(void)
{
	return (LINEMATE_CHANCE + DERAUMERE_CHANCE + SIBUR_CHANCE + \
			MENDIANE_CHANCE + PHIRAS_CHANCE + THYSTAME_CHANCE + FOOD_CHANCE);
}

static void	spawn_resource(t_tile *t, int type)
{
	gfx_sendall("SPAWN_RESOURCE %d %d %d\n", t->x, t->y, type);
	t->count[type] += 1;
}

void		spawn_random_resource_on_tile(t_tile *t)
{
	unsigned int	r;
	unsigned int	accumulator;

	accumulator = 0;
	r = random() % sum_resource_chances();
	if (r < (accumulator += FOOD_CHANCE))
		spawn_resource(t, FOOD);
	else if (r < (accumulator += LINEMATE_CHANCE))
		spawn_resource(t, LINEMATE);
	else if (r < (accumulator += DERAUMERE_CHANCE))
		spawn_resource(t, DERAUMERE);
	else if (r < (accumulator += SIBUR_CHANCE))
		spawn_resource(t, SIBUR);
	else if (r < (accumulator += MENDIANE_CHANCE))
		spawn_resource(t, MENDIANE);
	else if (r < (accumulator += PHIRAS_CHANCE))
		spawn_resource(t, PHIRAS);
	else
		spawn_resource(t, THYSTAME);
}

void		do_per_tick_resource_generation(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_map->dim.x)
	{
		j = 0;
		while (j < g_map->dim.y)
		{
			if (random() % SPAWN_CHANCE_DENOMINATOR < SPAWN_CHANCE_NUMERATOR)
				spawn_random_resource_on_tile(&g_map->tile[i][j]);
			++j;
		}
		++i;
	}
}

void		seed_tiles_initial_resources(void)
{
	int		i;

	i = 0;
	while (i < PREGAME_RESOURCE_SPAWNING_ROUNDS)
	{
		do_per_tick_resource_generation();
		++i;
	}
}
