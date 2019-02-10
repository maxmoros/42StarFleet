/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:20 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:20 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "tile_type.h"
#include "player_type.h"

static char *g_obj_names[] =
{
	[LINEMATE] = "linemate",
	[DERAUMERE] = "deraumere",
	[SIBUR] = "sibur",
	[MENDIANE] = "mendiane",
	[PHIRAS] = "phiras",
	[THYSTAME] = "thystame",
	[FOOD] = SERVER_STRING_FOOD,
	[PLAYERS] = SERVER_STRING_PLAYER
};

size_t		alloc_space_for_seen_objects(t_objcount **counts, char **str_p)
{
	int		type;
	size_t	len;
	int		i;

	len = strlen("{}\n");
	i = 0;
	while (counts[i])
	{
		type = 0;
		while (type < NUM_ENUMERATED_OBJECTS)
		{
			len += MAX_OBJ_NAME_LENGTH * counts[i][0][type] + strlen(" ");
			type++;
		}
		len += strlen(", ");
		i++;
	}
	*str_p = calloc(len + 1, sizeof(char));
	return (len);
}

int			append_stringified_objcount(char *s, t_objcount *ct)
{
	int			obj_left_to_print;
	int			num_printed_chars;
	int			type;
	int			i;

	obj_left_to_print = ct[0][LINEMATE] + ct[0][DERAUMERE]
		+ ct[0][SIBUR] + ct[0][MENDIANE] + ct[0][PHIRAS]
		+ ct[0][THYSTAME] + ct[0][FOOD] + ct[0][PLAYERS];
	num_printed_chars = 0;
	type = 0;
	while (type < NUM_ENUMERATED_OBJECTS)
	{
		i = 0;
		while (i < ct[0][type])
		{
			num_printed_chars += sprintf(s + num_printed_chars, "%s%s",
					g_obj_names[type], obj_left_to_print == 1 ? "" : " ");
			obj_left_to_print--;
			i++;
		}
		type++;
	}
	return (num_printed_chars);
}

char		*stringify_seen_tiles(t_objcount **counts)
{
	char	*res;
	int		i;
	char	*end;

	alloc_space_for_seen_objects(counts, &res);
	end = res;
	end += sprintf(end, "{");
	i = 0;
	while (counts[i])
	{
		end += append_stringified_objcount(end, counts[i]);
		if (counts[i + 1] != NULL)
			end += sprintf(end, ", ");
		i++;
	}
	sprintf(end, "}\n");
	return (res);
}

t_objcount	**get_visible_tile_objcounts(t_player *p)
{
	t_objcount	**counts;
	int			col;
	int			row;
	t_tile		*head;
	t_tile		*iter;

	counts = calloc(1 + (p->level + 1) * (p->level + 1), sizeof(*counts));
	row = 0;
	head = p->tile;
	while (row <= p->level)
	{
		col = 0;
		iter = head;
		while (col <= row * 2)
		{
			counts[row * row + col] = &iter->count;
			iter = get_adj_tile(iter, direction_add(p->facing, EAST));
			col++;
		}
		head = get_adj_tile(head, direction_add(p->facing, NORTHWEST));
		row++;
	}
	return (counts);
}

char		*see(int player_id, void *args)
{
	char		*str;
	t_objcount	**cts;
	t_player	*player;

	(void)args;
	player = get_player(player_id);
	player->tile->count[PLAYERS] -= 1;
	cts = get_visible_tile_objcounts(player);
	str = stringify_seen_tiles(cts);
	player->tile->count[PLAYERS] += 1;
	gfx_sendall("SEE %d\n", player->id);
	free(cts);
	return (str);
}
