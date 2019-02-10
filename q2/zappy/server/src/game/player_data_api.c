/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data_api.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:09 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:09 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "g_player_list.h"

t_player	**g_player_list = NULL;
int			g_list_size = START_SIZE;

int				grow_list(void)
{
	g_player_list = realloc(g_player_list,
			sizeof(t_player *) * (g_list_size * 2));
	if (!g_player_list)
		ERR_OUT("grow list; realloc");
	bzero(g_player_list + g_list_size, g_list_size);
	g_list_size *= 2;
	return (0);
}

void			player_list_init(void)
{
	if ((g_player_list = calloc(START_SIZE, sizeof(t_player *))) == NULL)
		ERR_OUT("player list; malloc");
	g_list_size = START_SIZE;
}

int				add_player_to_list(t_player *t)
{
	while (t->id >= g_list_size)
		grow_list();
	g_player_list[t->id] = t;
	return (0);
}

t_player		*get_player(int pid)
{
	if (pid >= g_list_size)
		return (NULL);
	return (g_player_list[pid]);
}
