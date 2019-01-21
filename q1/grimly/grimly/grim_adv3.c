/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_adv3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:14:44 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/13 17:03:10 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		grim_u(char ***map, t_actor *node, int *xy)
{
	node->y--;
	map[1][node->y][node->x] = 0x08;
	if (node->x == xy[4] && node->y == xy[5])
		return (-1);
	return (1);
}

int		grim_l(char ***map, t_actor *node, int *xy)
{
	node->x--;
	map[1][node->y][node->x] = 0x04;
	if (node->x == xy[4] && node->y == xy[5])
		return (-1);
	return (1);
}

int		grim_r(char ***map, t_actor *node, int *xy)
{
	node->x++;
	map[1][node->y][node->x] = 0x02;
	if (node->x == xy[4] && node->y == xy[5])
		return (-1);
	return (1);
}

int		grim_d(char ***map, t_actor *node, int *xy)
{
	node->y++;
	map[1][node->y][node->x] = 0x01;
	if (node->x == xy[4] && node->y == xy[5])
		return (-1);
	return (1);
}
