/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_geng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:00:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 20:39:06 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		draw(t_wolf *node, int x, int *image)
{
	int		y;
	int		top;
	int		bottom;
	int		tmp;

	y = -1;
	tmp = (int)(600 / node->ray->pwdst);
	top = tmp / 2 + 300;
	bottom = 300 - tmp / 2;
	x++;
	while (++y < 600)
	{
		ft_putnbr(y);
		if (y < bottom || y > top)
			image[y] = 0x000000;
		else
			image[y] = 0xAAFFAA;
	}
	return (1);
}

int		geng(t_wolf *node)
{
	int		x;
	void	*image;

	x = -1;
	move_player(node);
	image = mlx_new_image(node->mlx, 600, 600);
	while (++x < 600)
	{
		init_ray(node, 2.0 * x / 600 - 1.0);
		draw(node, x, image);
	}
	mlx_put_image_to_window(node->mlx, node->window, image, 0, 0);
	mlx_destroy_image(node->mlx, image);
	return (1);
}
