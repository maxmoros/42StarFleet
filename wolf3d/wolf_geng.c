/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 12:28:35 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		draw(t_wolf *node)
{
	if (node)
		;
	return (1);
}

int		geng(t_wolf *node)
{
	if (node->io->a && node->io->d)
	{
		init_ray(node, 0);
		printf("distance is %f\n", node->ray->pwdst);
	}
	return (1);
}
