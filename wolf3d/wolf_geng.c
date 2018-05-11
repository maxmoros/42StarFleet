/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 20:23:26 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		draw(t_wolf *node, int x)
{
	int		y;
	int		top;
	int		bottom;
	int		tmp;

	y = -1;
	tmp = (int)(RESY / node->ray->pwdst);
	top = tmp / 2 + RESY / 2;
	bottom = RESY / 2 - tmp / 2;
	while (++y < RESY)
	{
		if (y < bottom || y > top)
			pixel_to_img(node, x, y, 0x00000000);
		else if (node->ray->side)
			pixel_to_img(node, x, y, 0x00AAFFAA);
		else
			pixel_to_img(node, x, y, 0x00668866);
	}
	return (1);
}

int		geng(t_wolf *node)
{
	int		x;

	x = -1;
	move_player(node);
	while (++x < RESX)
	{
		init_ray(node, 2.0 * x / RESX - 1.0);
		draw(node, x);
	}
	mlx_put_image_to_window(node->mlx, node->window, node->img->ptr, 0, 0);
	return (1);
}
