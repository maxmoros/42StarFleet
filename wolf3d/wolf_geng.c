/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 18:01:00 by mmoros           ###   ########.fr       */
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
	x++;
	while (++y < RESY)
	{
		ft_putnbr(y);
		if (y < bottom || y > top)
			*(node->img>img + y) = 0x000000;
		else
			*(image + y) = 0xAAFFAA;
	}
	return (1);
}

int		geng(t_wolf *node)
{
	int		x;

	x = -1;
	move_player(node);
	init_img(node);
	while (++x < RESX)
	{
		init_ray(node, 2.0 * x / RESX - 1.0);
		draw(node, x);
	}
	mlx_put_image_to_window(node->mlx, node->window, node->img->ptr, 0, 0);
	mlx_destroy_image(node->mlx, node->img->img);
	return (1);
}
