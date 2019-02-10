/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_take.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:25 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:25 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "tile_type.h"

static char *g_object_names_by_type[NUM_ENUMERATED_OBJECTS] = {
	[PLAYERS] = SERVER_STRING_PLAYER,
	[LINEMATE] = "linemate",
	[DERAUMERE] = "deraumere",
	[SIBUR] = "sibur",
	[MENDIANE] = "mendiane",
	[PHIRAS] = "phiras",
	[THYSTAME] = "thystame",
	[FOOD] = SERVER_STRING_FOOD,
};

enum e_object_type	get_object_type(char *object_name)
{
	enum e_object_type type;

	type = 0;
	while (type < NUM_ENUMERATED_OBJECTS)
	{
		if (!strcmp(g_object_names_by_type[type], object_name))
			return (type);
		type++;
	}
	return (-1);
}

char				*put(int player_id, void *args)
{
	t_player	*p;
	int			object_type;
	int			success;

	object_type = get_object_type(args);
	p = get_player(player_id);
	success = 0;
	if (object_type != -1 && p->count[object_type] >= 1)
	{
		p->count[object_type] -= 1;
		p->tile->count[object_type] += 1;
		success = 1;
	}
	gfx_sendall("PUT %d %d %d %d %d\n",
			p->id, object_type, p->tile->x, p->tile->y, success);
	return (success ? ok_response() : ko_response());
}

char				*take(int player_id, void *args)
{
	t_player	*p;
	int			object_type;
	int			success;

	object_type = get_object_type(args);
	p = get_player(player_id);
	success = 0;
	if (object_type != -1 && p->tile->count[object_type] >= 1)
	{
		p->tile->count[object_type] -= 1;
		p->count[object_type] += 1;
		success = 1;
	}
	gfx_sendall("TAKE %d %d %d %d %d\n",
			p->id, object_type, p->tile->x, p->tile->y, success);
	return (success ? ok_response() : ko_response());
}
