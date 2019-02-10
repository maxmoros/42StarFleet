/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:38 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:38 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "client_type.h"
#include "clients_lookup.h"

t_tile		*iter_tiles(void)
{
	static int	prev_x = 0;
	static int	prev_y = -1;
	int			x;
	int			y;

	if (prev_x == g_map->dim.x - 1 && prev_y == g_map->dim.y - 1)
	{
		prev_x = 0;
		prev_y = -1;
		return (NULL);
	}
	else if (prev_y == g_map->dim.y - 1)
	{
		x = prev_x + 1;
		y = 0;
	}
	else
	{
		x = prev_x;
		y = prev_y + 1;
	}
	prev_y = y;
	prev_x = x;
	return (&g_map->tile[x][y]);
}

t_player	*iter_players(void)
{
	static int	players_to_find = -1;
	static int	found_players = -1;
	static int	next_pid = 0;
	int			this_pid;
	t_player	*p;

	if (players_to_find == -1)
	{
		players_to_find = g_map->players;
		found_players = 0;
		next_pid = 0;
	}
	if (found_players == players_to_find)
	{
		players_to_find = -1;
		return (NULL);
	}
	this_pid = next_pid;
	while ((p = get_player(this_pid)) == NULL)
	{
		this_pid++;
	}
	found_players++;
	next_pid = this_pid + 1;
	return (p);
}

t_client	*iter_clients(int type)
{
	static t_client	**clients = NULL;
	t_client		*c;

	if (clients == NULL)
		clients = g_clients;
	while (1)
	{
		c = *clients++;
		if (type == -1 || c == NULL || c->type == type)
			break ;
	}
	if (c == NULL)
		clients = NULL;
	return (c);
}
