/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_visuals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:49 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:49 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_type.h"
#include "player_type.h"
#include "tile_type.h"
#include "server.h"

t_player		*client_controlled_player_on_tile(t_tile *t)
{
	t_player	*p;
	t_client	*c;
	int			i;

	i = 0;
	while (i < t->count[PLAYERS])
	{
		p = t->players[i];
		if (p && (c = get_client_by_id(p->id)) && c->type == ACTIVE_PLAYER)
			return (p);
		i++;
	}
	return (NULL);
}

void			print_tile(t_tile *t)
{
	t_player	*p;

	if (t->count[PLAYERS] == 0)
		printf(". ");
	else if ((p = client_controlled_player_on_tile(t)))
		printf("%c ", "^^<<vv>>"[p->facing]);
	else if (t->count[PLAYERS] <= 9)
		printf("%d ", t->count[PLAYERS]);
	else
		printf("? ");
}

#ifdef ASCII_ANIMATIONS

void			animate(void)
{
	static int	ticks;
	int			row;
	int			col;

	system("clear");
	printf("[0-9] = num empty bodies, (? if > 9), >^<v = connected client\n\n");
	printf("x = %d, y = %d. port = %d. tick %d\n",
			g_map->dim.x, g_map->dim.y, g_opts.server_port, ticks);
	row = 0;
	while (row < g_map->dim.y)
	{
		col = 0;
		while (col < g_map->dim.x)
		{
			print_tile(&g_map->tile[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
	fflush(stdout);
	ticks++;
}

#else

void			animate(void)
{
	static int ticks;

	if (ticks == 0)
	{
		printf("each . = 126 ticks, or | for 1260. server port = %d\n",
				g_opts.server_port);
	}
	else if (ticks % 126 == 0)
	{
		if (ticks % 1260 == 0)
			printf("|");
		else
			printf(".");
	}
	fflush(stdout);
	ticks++;
}

#endif
