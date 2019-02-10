/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hatch_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:39 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:39 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "hatch_queue.h"
#include "delays.h"

struct s_hatch_queue		g_hatch_queue =
{
	.head = NULL,
	.tail = NULL,
	.length = 0
};

void						enqueue_player_egg(int x, int y, int team_id)
{
	struct s_player_egg	*egg;

	egg = malloc(sizeof(*egg));
	egg->x = x;
	egg->y = y;
	egg->team_id = team_id;
	egg->timer = DELAY_TIMER_EGG_HATCH;
	egg->next = NULL;
	if (g_hatch_queue.head == NULL)
	{
		g_hatch_queue.head = egg;
		g_hatch_queue.tail = egg;
	}
	else
	{
		g_hatch_queue.tail->next = egg;
		g_hatch_queue.tail = egg;
	}
	g_hatch_queue.length += 1;
}

void						check_and_hatch_eggs(void)
{
	t_player			*p;
	struct s_player_egg	*egg;

	while ((egg = g_hatch_queue.head) && egg->timer == 0)
	{
		p = new_player(egg->team_id);
		add_player_to_tile(p, &g_map->tile[egg->x][egg->y]);
		p->tile->eggs -= 1;
		gfx_sendall("EGG_HATCH %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
			p->id, p->team_id, p->level, p->tile->x, p->tile->y, p->energy,
			p->facing, p->count[FOOD], get_client_by_id(p->id) != NULL,
			p->count[LINEMATE], p->count[DERAUMERE], p->count[SIBUR],
			p->count[MENDIANE], p->count[PHIRAS], p->count[THYSTAME]);
		g_hatch_queue.length -= 1;
		g_hatch_queue.head = egg->next;
		free(egg);
	}
	while (egg)
	{
		egg->timer -= 1;
		egg = egg->next;
	}
}
