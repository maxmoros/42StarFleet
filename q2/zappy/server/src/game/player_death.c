/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:04 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:04 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

#define OBIT_START_SIZE 8

static int		*g_dead_pids = NULL;
static int		g_obit_size = 0;
static int		g_dead_num = 0;

void			remove_dead_plist_node(t_player *p)
{
	t_plist		*prev;
	t_plist		*curr;

	if (!g_map->empty_avatars[p->team_id])
		return ;
	if (g_map->empty_avatars[p->team_id]->p == p)
		remove_player_from_waitlist(p->team_id);
	else
	{
		prev = g_map->empty_avatars[p->team_id];
		curr = prev->next;
		while (curr != NULL && curr->p != p)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr && curr->p == p)
		{
			prev->next = curr->next;
			free(curr);
		}
	}
}

int				*kill_and_return_dead_players(int *size)
{
	int			i;
	t_player	*p;

	*size = g_dead_num;
	i = 0;
	while (i < g_dead_num)
	{
		p = get_player(g_dead_pids[i]);
		g_map->players_on_team[p->team_id] -= 1;
		remove_dead_plist_node(p);
		delete_player_from_list(p);
		i++;
	}
	g_map->players -= g_dead_num;
	g_dead_num = 0;
	return (g_dead_pids);
}

int				mark_player_for_death(t_player *p)
{
	if (!g_dead_pids)
	{
		g_obit_size = OBIT_START_SIZE;
		g_dead_pids = calloc(g_obit_size, sizeof(int));
	}
	if (g_dead_num == g_obit_size)
		g_dead_pids = realloc(g_dead_pids, (g_obit_size *= 2) * sizeof(int));
	remove_player_from_tile(p, p->tile);
	g_dead_pids[g_dead_num] = p->id;
	g_dead_num++;
	return (0);
}
