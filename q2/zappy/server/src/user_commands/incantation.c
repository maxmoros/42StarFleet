/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:26 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:26 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "command_type.h"
#include "client_type.h"
#include "incantation.h"
#include "tile_type.h"

t_objcount	g_incant_reqs[7] =
{
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 2 },
	{ 2, 0, 1, 0, 2, 0, 0, 2 },
	{ 1, 1, 2, 0, 1, 0, 0, 4 },
	{ 1, 2, 1, 3, 0, 0, 0, 4 },
	{ 1, 2, 3, 0, 1, 0, 0, 6 },
	{ 2, 2, 2, 2, 2, 1, 0, 6 }
};

void					construct_totem(t_tile *t, int priest_level,
		struct s_incant_args *result)
{
	int		i;

	i = MIN_STONE;
	while (i <= MAX_STONE)
	{
		t->count[i] -= g_incant_reqs[priest_level - 1][i];
		gfx_sendall("USE_STONE_FOR_TOTEM %d %d\n",
				i, g_incant_reqs[priest_level - 1][i]);
		i++;
	}
	i = 0;
	while (i < result->group_size)
	{
		if (result->levelup_group[i] != result->priest_id)
			gfx_sendall("JOIN_RITUAL %d\n", result->levelup_group[i]);
		i++;
	}
}

void					add_potential_ritual_participants(
		t_player *priest, struct s_incant_args *result)
{
	int		i;
	int		j;
	t_tile	*priest_tile;

	priest_tile = priest->tile;
	result->levelup_group = calloc(priest_tile->count[PLAYERS], sizeof(int));
	result->group_size = priest_tile->count[PLAYERS];
	i = 0;
	j = 0;
	while (i < priest_tile->count[PLAYERS])
	{
		if (priest_tile->players[i]->level == priest->level)
			result->levelup_group[j++] = priest_tile->players[i]->id;
		else
			result->group_size -= 1;
		i++;
	}
}

char					*incantation_finish(int priest_id, void *args)
{
	t_player				*player;
	int						i;
	struct s_incant_args	*result;
	char					*response;

	result = (struct s_incant_args *)args;
	i = 0;
	gfx_sendall("INCANT_FINISH %d %d\n", priest_id, result->new_level);
	while (i < result->group_size)
	{
		player = get_player(result->levelup_group[i]);
		if (player != NULL && player->level < result->new_level)
		{
			increase_player_level(player, result->new_level);
			gfx_sendall("LEVEL_UP %d %d\n", player->id, result->new_level);
		}
		++i;
	}
	gfx_sendall("%s", "DONE\n");
	asprintf(&response, "current level %d\n", get_player(priest_id)->level);
	free(result->levelup_group);
	return (response);
}

struct s_incant_args	*get_eventual_incantation_result(t_player *priest)
{
	struct s_incant_args	*result;
	int						*reqs;

	result = malloc(sizeof(*result));
	add_potential_ritual_participants(priest, result);
	reqs = g_incant_reqs[priest->level - 1];
	result->new_level = priest->level;
	if (priest->level < 8
			&& reqs[PLAYERS] <= result->group_size
			&& reqs[LINEMATE] <= priest->tile->count[LINEMATE]
			&& reqs[DERAUMERE] <= priest->tile->count[DERAUMERE]
			&& reqs[SIBUR] <= priest->tile->count[SIBUR]
			&& reqs[MENDIANE] <= priest->tile->count[MENDIANE]
			&& reqs[PHIRAS] <= priest->tile->count[PHIRAS]
			&& reqs[THYSTAME] <= priest->tile->count[THYSTAME])
	{
		construct_totem(priest->tile, priest->level, result);
		result->new_level += 1;
	}
	else
		result->group_size = 1;
	gfx_sendall("LEAD_RITUAL %d %d %d %d\n", priest->id,
			result->new_level > priest->level,
			result->new_level, result->group_size);
	return (result);
}

char					*incantation(int player_id, void *args)
{
	t_command				*ritual_completion_command;
	t_ply_cmd_queue			*q;
	struct s_incant_args	*result;
	char					*response;

	(void)args;
	gfx_sendall("%s", "INCANT_START\n");
	ritual_completion_command = new_cmd(incantation_finish);
	ritual_completion_command->player_id = player_id;
	result = get_eventual_incantation_result(get_player(player_id));
	result->priest_id = player_id;
	ritual_completion_command->args = (char *)result;
	q = &(get_client_by_id(player_id)->cmdqueue);
	if (q->size >= MAX_COMMANDS)
		q->size -= 1;
	ply_enqueue_front(q, ritual_completion_command);
	gfx_sendall("%s", "DONE\n");
	asprintf(&response, "elevation in progress\n");
	return (response);
}
