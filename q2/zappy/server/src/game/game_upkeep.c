/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_upkeep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:10 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:10 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

void	feed_players(void)
{
	t_player	*p;

	while ((p = iter_players()))
	{
		p->energy--;
		if (p->energy <= 0 && p->count[FOOD] > 0)
		{
			p->count[FOOD]--;
			gfx_sendall("EAT_FOOD %d\n", p->id);
			p->energy = ENERGY_PER_FOOD;
		}
		else if (p->energy <= 0)
			mark_player_for_death(p);
	}
}

void	game_upkeep(void)
{
	feed_players();
	do_per_tick_resource_generation();
}
