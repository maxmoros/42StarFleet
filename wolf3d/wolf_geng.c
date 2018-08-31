/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/30 19:20:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	pick_texture(int top, int bottom, int y, t_wolf *node)
{
	int		tex_x;
	int		tex_y;

	tex_x = (int)(node->ray->wallx * TEXX);
	tex_y = (int)((y - bottom) * TEXY / (top - bottom));
	return (img_to_pixel(node->tex[(int)node->ray->side], tex_x, tex_y));
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
			pixel_to_img(node->img, x, y, 0x00444444);
		else if (y < bottom)
			pixel_to_img(node->img, x, y, 0x00000066);
		else
			pixel_to_img(node->img, x, y, pick_texture(top, bottom, y, node));
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
