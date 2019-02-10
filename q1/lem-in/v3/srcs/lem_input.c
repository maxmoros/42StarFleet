/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:50:39 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/09 20:54:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		link_rooms(char *room1, char *room2)
{
	int		r1;
	int		r2;
	t_room	*node1;
	t_room	*node2;

	r1 = 0;
	r2 = 0;
	node1 = g_lem.rooms;
	node2 = g_lem.rooms;
	while (ft_strcmp(node1->name, room1) && ++r1)
		node1 = node1->next;
	while (ft_strcmp(node2->name, room2) && ++r2)
		node2 = node2->next;
	node1->adjc[r2] = 1;
	node2->adjc[r1] = 1;
}

static int		line_path(char *line, int i)
{
	char	**parts;
	int		ret;

	ret = 1;
	parts = ft_strsplit(line, '-');
	while (parts[++i])
		;
	if (i != 2 || !valid_name(parts[0]) || !valid_name(parts[1]))
		ret = 0;
	else if (g_lem.check & PATH)
	{
		link_rooms(parts[0], parts[1]);
		if (g_lem.verbose)
		{
			ft_putstr("link from ");
			ft_putstr(parts[0]);
			ft_putstr(" to ");
			ft_putstr(parts[1]);
			ft_putstr("\n");
		}
	}
	while (i-- > 0)
		free(parts[i]);
	free(parts);
	return (ret);
}

static int		ht_line(char *line)
{
	t_room	*node;

	ft_putstr(line);
	ft_putstr("\n");
	if (!ft_strcmp(line, "##start"))
	{
		if ((g_lem.check & 0x01) || !(g_lem.check |= 0x01)
				|| get_next_line(0, &line) != 1
				|| !(g_lem.rooms = line_room(line, g_lem.rooms))
				|| free_ret(line, 0))
			return (0);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		node = g_lem.rooms;
		while (node && node->next)
			node = node->next;
		if ((g_lem.check & 0x02) || !(g_lem.check |= 0x02)
				|| get_next_line(0, &line) != 1)
			return (0);
		if ((node && !(node->next = line_room(line, NULL))) || (!node &&
				!(g_lem.rooms = line_room(line, NULL))) || free_ret(line, 0))
			return (0);
	}
	return (1);
}

static int		data_line(char *line)
{
	if (!(g_lem.check & PATH) && !line_path(line, -1))
	{
		if (g_lem.check & START)
		{
			if (!(g_lem.rooms->next = line_room(line, g_lem.rooms->next)))
				return (0);
		}
		else if (!(g_lem.rooms = line_room(line, g_lem.rooms)))
			return (0);
	}
	else if (!(g_lem.check & PATH))
	{
		g_lem.check |= PATH;
		if (!count_rooms() || !line_path(line, -1))
			return (0);
	}
	else if (!line_path(line, -1))
		return (0);
	return (1);
}

int				build_map(void)
{
	char	*line;

	ft_putstr("\n   BUILDING MAP\n");
	while (get_next_line(0, &line) == 1 && line[0])
	{
		if (!(line[0] == '#' ? ht_line(line) : data_line(line)))
		{
			ft_putstr("Invalid line : \"");
			ft_putstr(line);
			ft_putstr("\"\n");
			free(line);
			return (0);
		}
		free(line);
	}
	return (g_lem.check == 0x07 ? 1 : 0);
}
