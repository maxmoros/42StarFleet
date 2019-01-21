/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_adv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 17:36:24 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/13 17:02:58 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		grim_ulr(char ***map, t_actor *node, int *xy)
{
	t_actor		*left;
	t_actor		*right;

	right = grim_actor(node->next, node->x + 1, node->y);
	left = grim_actor(right, node->x - 1, node->y);
	node->next = left;
	node->y--;
	map[1][node->y][node->x] = 0x08;
	map[1][left->y][left->x] = 0x04;
	map[1][right->y][right->x] = 0x02;
	if ((node->x == xy[4] && node->y == xy[5]) ||
			(left->x == xy[4] && left->y == xy[5]) ||
			(right->x == xy[4] && right->y == xy[5]))
		return (-1);
	return (3);
}

int		grim_uld(char ***map, t_actor *node, int *xy)
{
	t_actor		*left;
	t_actor		*down;

	down = grim_actor(node->next, node->x, node->y + 1);
	left = grim_actor(down, node->x - 1, node->y);
	node->next = left;
	node->y--;
	map[1][node->y][node->x] = 0x08;
	map[1][left->y][left->x] = 0x04;
	map[1][down->y][down->x] = 0x01;
	if ((node->x == xy[4] && node->y == xy[5]) ||
			(left->x == xy[4] && left->y == xy[5]) ||
			(down->x == xy[4] && down->y == xy[5]))
		return (-1);
	return (3);
}

int		grim_urd(char ***map, t_actor *node, int *xy)
{
	t_actor		*right;
	t_actor		*down;

	down = grim_actor(node->next, node->x, node->y + 1);
	right = grim_actor(down, node->x + 1, node->y);
	node->next = right;
	node->y--;
	map[1][node->y][node->x] = 0x08;
	map[1][right->y][right->x] = 0x02;
	map[1][down->y][down->x] = 0x01;
	if ((node->x == xy[4] && node->y == xy[5]) ||
			(right->x == xy[4] && right->y == xy[5]) ||
			(down->x == xy[4] && down->y == xy[5]))
		return (-1);
	return (3);
}

int		grim_lrd(char ***map, t_actor *node, int *xy)
{
	t_actor		*right;
	t_actor		*down;

	down = grim_actor(node->next, node->x, node->y + 1);
	right = grim_actor(down, node->x + 1, node->y);
	node->next = right;
	node->x--;
	map[1][node->y][node->x] = 0x04;
	map[1][right->y][right->x] = 0x02;
	map[1][down->y][down->x] = 0x01;
	if ((node->x == xy[4] && node->y == xy[5]) ||
			(right->x == xy[4] && right->y == xy[5]) ||
			(down->x == xy[4] && down->y == xy[5]))
		return (-1);
	return (3);
}

int		grim_rd(char ***map, t_actor *node, int *xy)
{
	t_actor		*down;

	down = grim_actor(node->next, node->x, node->y + 1);
	node->next = down;
	node->x++;
	map[1][node->y][node->x] = 0x02;
	map[1][down->y][down->x] = 0x01;
	if ((node->x == xy[4] && node->y == xy[5]) ||
			(down->x == xy[4] && down->y == xy[5]))
		return (-1);
	return (2);
}
