/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:07:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/13 17:04:27 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		grim_advance_a(char ***map, t_actor *node, int *xy)
{
	if (node->x && !map[1][node->y][node->x - 1])
	{
		if (node->x < xy[0] - 1 && !map[1][node->y][node->x + 1])
			return (grim_ulr(map, node, xy));
		else if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
			return (grim_uld(map, node, xy));
		else
			return (grim_ul(map, node, xy));
	}
	else if (node->x < xy[0] - 1 && !map[1][node->y][node->x + 1])
	{
		if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
			return (grim_urd(map, node, xy));
		else
			return (grim_ur(map, node, xy));
	}
	else if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
		return (grim_ud(map, node, xy));
	else
		return (grim_u(map, node, xy));
	return (1);
}

int		grim_advance_b(char ***map, t_actor *node, int *xy)
{
	if (node->x && !map[1][node->y][node->x - 1])
	{
		if (node->x < xy[0] - 1 && !map[1][node->y][node->x + 1])
		{
			if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
				return (grim_lrd(map, node, xy));
			else
				return (grim_lr(map, node, xy));
		}
		else if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
			return (grim_ld(map, node, xy));
		else
			return (grim_l(map, node, xy));
	}
	else if (node->x < xy[0] - 1 && !map[1][node->y][node->x + 1])
	{
		if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
			return (grim_rd(map, node, xy));
		else
			return (grim_r(map, node, xy));
	}
	else if (node->y < xy[1] - 1 && !map[1][node->y + 1][node->x])
		return (grim_d(map, node, xy));
	else
		return (grim_del(&node));
}

void	grim_path(char ***map, int x, int y, int *xy)
{
	if (map[1][y][x] & 0x01)
		map[1][y--][x] = '2';
	else if (map[1][y][x] & 0x02)
		map[1][y][x--] = '2';
	else if (map[1][y][x] & 0x04)
		map[1][y][x++] = '2';
	else
		map[1][y++][x] = '2';
	while (map[1][y][x] != '1')
	{
		xy[6]++;
		if (map[1][y][x] == 0x01)
			map[1][y--][x] = 'o';
		else if (map[1][y][x] == 0x02)
			map[1][y][x--] = 'o';
		else if (map[1][y][x] == 0x04)
			map[1][y][x++] = 'o';
		else
			map[1][y++][x] = 'o';
	}
}

int		grim_solve(char ***map, int *xy)
{
	t_actor		*node;
	int			i;

	node = grim_actor(NULL, xy[2], xy[3]);
	node->next = node;
	while (node)
	{
		if (node->y && !map[1][node->y - 1][node->x])
		{
			if ((i = grim_advance_a(map, node, xy)) < 0)
				break ;
		}
		else if ((i = grim_advance_b(map, node, xy)) < 0)
			break ;
		while (i--)
			node = node->next;
	}
	if (map[1][xy[5]][xy[4]])
		grim_path(map, xy[4], xy[5], xy);
	else
		return (0);
	free_actors(node);
	return (1);
}
