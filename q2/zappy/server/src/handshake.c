/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handshake.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:47 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:47 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "client_type.h"
#include "tile_type.h"
#include "clients_lookup.h"
#include "delays.h"

#define MEANINGLESS_GFX_CLIENT_ID -1
#define GFX_CLIENT_SECRET_KEY "-banana"

void		initiate_handshake(int serv_fd)
{
	int					cli_fd;
	struct sockaddr_in	client_addr;
	socklen_t			len;

	len = sizeof(struct sockaddr);
	if ((cli_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &len)) == -1)
		perror("handshake accept");
	else
	{
		if (send(cli_fd, SERVER_STRING_WELCOME,
					strlen(SERVER_STRING_WELCOME), 0) == -1)
			perror("send welcome");
		else
			socket_lookup_add(cli_fd, HANDSHAKE);
	}
}

static void	finish_new_player_handshake(int fd, char *client_msg)
{
	char	response[256];
	int		open_slots;
	int		team_id;
	int		player_id;

	if ((team_id = team_name_to_id(client_msg)) == -1)
		return (socket_lookup_remove(fd, 1));
	if ((open_slots = get_team_open_slots(team_id)) <= 0)
		return (socket_lookup_remove(fd, 1));
	snprintf(response, sizeof(response), "%d\n%d %d\n",
			open_slots, g_opts.world_width, g_opts.world_height);
	send(fd, response, strlen(response), 0);
	player_id = assign_avatar(team_id);
	register_client(fd, player_id, ACTIVE_PLAYER);
	gfx_sendall("CONNECT %d\n", player_id);
}

static void	send_command_tick_delays(int fd)
{
	gfx_sendone(fd, "DELAY_TIME SEE %d\n", DELAY_TIMER_SEE);
	gfx_sendone(fd, "DELAY_TIME ADVANCE %d\n", DELAY_TIMER_ADVANCE);
	gfx_sendone(fd, "DELAY_TIME RIGHT %d\n", DELAY_TIMER_RIGHT);
	gfx_sendone(fd, "DELAY_TIME LEFT %d\n", DELAY_TIMER_LEFT);
	gfx_sendone(fd, "DELAY_TIME LEAD_RITUAL %d\n",
			DELAY_TIMER_FINISH_INCANT);
	gfx_sendone(fd, "DELAY_TIME KICK %d\n", DELAY_TIMER_KICK);
	gfx_sendone(fd, "DELAY_TIME BROADCAST %d\n",
			DELAY_TIMER_BROADCAST);
	gfx_sendone(fd, "DELAY_TIME TAKE %d\n", DELAY_TIMER_TAKE);
	gfx_sendone(fd, "DELAY_TIME PUT %d\n", DELAY_TIMER_PUT);
	gfx_sendone(fd, "DELAY_TIME LAY_EGG %d\n",
			DELAY_TIMER_LAY_EGG);
	gfx_sendone(fd, "DELAY_TIME EGG_HATCH %d\n",
			DELAY_TIMER_EGG_HATCH);
}

static void	finish_gfx_handshake(int fd)
{
	t_player	*p;
	t_tile		*t;
	int			i;

	register_client(fd, MEANINGLESS_GFX_CLIENT_ID, GFX);
	gfx_sendone(fd, "TICK %d\n", get_elapsed_ticks());
	gfx_sendone(fd, "WORLD %d %d %d\n", g_opts.world_width,
			g_opts.world_height, g_opts.tickrate);
	while ((t = iter_tiles()))
		gfx_sendone(fd, "TILE %d %d %d %d %d %d %d %d %d %d\n",
				t->x, t->y, t->eggs, t->count[FOOD],
				t->count[LINEMATE], t->count[DERAUMERE], t->count[SIBUR],
				t->count[MENDIANE], t->count[PHIRAS], t->count[THYSTAME]);
	i = 0;
	while (i < g_opts.teamcount)
		gfx_sendone(fd, "TEAMNAME %s\n", g_opts.team_names[i++]);
	while ((p = iter_players()))
		gfx_sendone(fd, "PLAYER %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
			p->id, p->team_id, p->level, p->tile->x, p->tile->y, p->energy,
			p->facing, p->count[FOOD], get_client_by_id(p->id) != NULL,
			p->count[LINEMATE], p->count[DERAUMERE], p->count[SIBUR],
			p->count[MENDIANE], p->count[PHIRAS], p->count[THYSTAME]);
	send_command_tick_delays(fd);
	gfx_sendone(fd, "%s", "DONE\n");
}

void		complete_handshake(int cli_fd)
{
	char	msg[MAX_TEAM_NAME_LENGTH + 1];

	if (recv(cli_fd, msg, MAX_TEAM_NAME_LENGTH, 0) <= 0)
		return (socket_lookup_remove(cli_fd, 1));
	if (g_count_clients == MAX_CLIENTS)
	{
		fputs("Aborting handshake; already at capacity\n", stderr);
		return (socket_lookup_remove(cli_fd, 1));
	}
	msg[strcspn(msg, "\n")] = '\0';
	if (!strcmp(GFX_CLIENT_SECRET_KEY, msg))
		finish_gfx_handshake(cli_fd);
	else
		finish_new_player_handshake(cli_fd, msg);
}
