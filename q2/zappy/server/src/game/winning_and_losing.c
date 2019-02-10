/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winning_and_losing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:58 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:58 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_type.h"
#include "hatch_queue.h"

#define MAX_LEVEL 8
#define LEVELCAPPED_PLAYERS_TO_WIN 6

static int g_num_winners = 0;
static int *g_winning_team_ids;

void	increase_player_level(t_player *p, int new_level)
{
	static int *team_players_at_max_level;

	if (!team_players_at_max_level)
		team_players_at_max_level = calloc(g_opts.teamcount, sizeof(int));
	assert(p->level < new_level);
	p->level = new_level;
	if (new_level == MAX_LEVEL)
		team_players_at_max_level[p->team_id] += 1;
	if (team_players_at_max_level[p->team_id] == LEVELCAPPED_PLAYERS_TO_WIN)
	{
		if (!g_winning_team_ids)
			g_winning_team_ids = calloc(g_opts.teamcount, sizeof(int));
		g_winning_team_ids[g_num_winners] = p->team_id;
		++g_num_winners;
	}
}

int		is_everyone_dead(void)
{
	int		i;

	if (g_hatch_queue.length > 0)
		return (0);
	i = 0;
	while (i < g_opts.teamcount)
	{
		if (g_map->players_on_team[i] > 0)
			return (0);
		++i;
	}
	return (1);
}

int		get_winning_teams(int **team_ids_ptr)
{
	if (is_everyone_dead())
		return (-1);
	if (g_num_winners > 0)
	{
		*team_ids_ptr = malloc(g_num_winners * sizeof(int));
		memcpy(*team_ids_ptr, g_winning_team_ids, g_num_winners * sizeof(int));
	}
	return (g_num_winners);
}
