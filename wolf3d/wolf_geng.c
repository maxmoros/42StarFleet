/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/29 18:28:48 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	pick_colour(t_wolf *node)
{
	int		rgb[3];
	int		colour;
	t_ray	*ray;

	ray = node->ray;
	if (!ray->side)
	{
		rgb[0] = 0xAA;
		rgb[1] = 0xAA;
		rgb[2] = 0xAA;
		if (RAY_IN_MAP(0) && RAY_IN_MAP(1))
			rgb[node->map->xy[ray->mpos[0]][ray->mpos[1]] - '0' - 1] = 0xFF;
	}
	else
	{
		rgb[0] = 0x66;
		rgb[1] = 0x66;
		rgb[2] = 0x66;
		if (RAY_IN_MAP(0) && RAY_IN_MAP(1))
			rgb[node->map->xy[ray->mpos[0]][ray->mpos[1]] - '0' - 1] = 0x88;
	}
	colour = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (colour);
}

static int	draw(t_wolf *node, int x)
{
	int		y;
	int		top;
	int		bottom;
	int		tmp;

	y = -1;
	tmp = (int)(RESY / node->ray->pwdst);
	top = tmp / 2 + RESY / 2 + (int)(RESY * node->plr->z / node->ray->pwdst);
	bottom = RESY / 2 - tmp / 2 + (int)(RESY * node->plr->z / node->ray->pwdst);
	while (++y < RESY)
	{
		if (y > top)
			pixel_to_img(node, x, y, 0x00444444);
		else if (y < bottom)
			pixel_to_img(node, x, y, 0x00000000);
		else
			pixel_to_img(node, x, y, pick_colour(node));
	}
	return (1);
}

int			geng(t_wolf *node)
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
