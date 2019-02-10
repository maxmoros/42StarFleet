/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:43:33 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/09 18:05:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_list(t_room *room)
{
	if (room->next)
		free_list(room->next);
	free(room->name);
	free(room->adjc);
	free(room);
}

static void		free_lem(void)
{
	int		i;

	if (g_lem.rooms)
		free_list(g_lem.rooms);
	ft_putstr("rooms freed\n");
	if (g_lem.paths)
	{
		i = -1;
		while (g_lem.paths[++i])
		{
			free(g_lem.paths[i]->trail);
			free(g_lem.paths[i]);
		}
		free(g_lem.paths);
	}
	ft_putstr("paths freed\n");
	if (g_lem.map)
	{
		i = g_lem.room_count;
		while (i-- > 0)
			free(g_lem.map[i]);
		free(g_lem.map);
	}
	ft_putstr("Map freed\n");
}

void		exit_lem(char *error)
{
	ft_putstr("\x1b[31;1mERROR\n\x1b[0m");
	ft_putstr("  ");
	ft_putstr(error);
	ft_putstr("\n");
	free_lem();
	exit(1);
}

static void		lem_in(void)
{
	init_lem();
	if (!get_ants() || !build_map())
		exit_lem("  Invalid data in map!\n");
//	print_rooms();
	build_logic_map();
	ft_bzero(g_lem.occupied, sizeof(int) * g_lem.room_count);
	g_lem.occupied[0] = 1;
	bfs_map();
//	test_bfs();
	get_paths();

//	if (!build_logic_map())
//		exit_lem("  Bad Malloc...rare!\n");
//	if (!traverse_map())
//		exit_lem("  No Valid Path!\n");
//	map_path();
//	move_ants();
}

int				main(void)
{
	lem_in();
//	free_lem();
	return (0);
}
