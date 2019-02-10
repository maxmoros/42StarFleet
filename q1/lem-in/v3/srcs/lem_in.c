/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:43:33 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/09 21:08:11 by mmoros           ###   ########.fr       */
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
		free(g_lem.map);
	ft_putstr("Map freed\n");
}

void			exit_lem(char *error)
{
	ft_putstr("\x1b[31;1mERROR\n\x1b[0m");
	ft_putstr("  ");
	ft_putstr(error);
	ft_putstr("\n");
	free_lem();
	exit(1);
}

static void		lem_in(int verbose)
{
	init_lem(verbose);
	if (!get_ants() || !build_map())
		exit_lem("  Invalid data in map!\n");
	if (verbose)
		print_rooms();
	build_logic_map();
	if (!get_paths())
		exit_lem("  No Valid Path!\n");
	move_ants();
	ft_putstr("completed in ");
	ft_putnbr(g_lem.x[0] + g_lem.y[0] - 2);
	ft_putstr(" lines!\n   COMPLETED\n");
}

int				main(int ac, char **av)
{
	if (ac == 2 && !ft_strcmp("-s", av[1]))
		lem_in(0);
	else
		lem_in(1);
	free_lem();
	return (0);
}
