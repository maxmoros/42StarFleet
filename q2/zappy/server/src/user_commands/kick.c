/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:22 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:22 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "tile_type.h"
#include "player_type.h"
#include "client_type.h"

char	*kick_origin_message(int kick_dir, t_player *p)
{
	static char msg[] = SERVER_STRING_MOVING;

	msg[strlen(msg) - 3] = '0'
		+ perceived_direction(opposite_direction(kick_dir), p);
	return (msg);
}

void	kick_and_alert_player(t_player *p, int dir)
{
	t_client	*client;
	char		*msg;

	move_player(p, dir);
	gfx_sendall("GET_KICKED %d %d\n", p->id, dir);
	if ((client = get_client_by_id(p->id)))
	{
		msg = kick_origin_message(dir, p);
		send(client->socket_fd, msg, strlen(msg), 0);
	}
}

char	*kick(int player_id, void *args)
{
	t_player	*kicker;
	t_player	**tile_players_copy;
	int			tile_player_count;
	int			i;

	(void)args;
	kicker = get_player(player_id);
	tile_player_count = kicker->tile->count[PLAYERS];
	gfx_sendall("KICK %d %d %d\n",
			player_id, kicker->facing, tile_player_count - 1);
	tile_players_copy = calloc(tile_player_count, sizeof(t_player *));
	memcpy(tile_players_copy, kicker->tile->players,
			tile_player_count * sizeof(t_player *));
	i = 0;
	while (i < tile_player_count)
	{
		if (tile_players_copy[i] != kicker)
			kick_and_alert_player(tile_players_copy[i], kicker->facing);
		i++;
	}
	gfx_sendall("%s", "DONE\n");
	free(tile_players_copy);
	return (tile_player_count > 1 ? ok_response() : ko_response());
}
