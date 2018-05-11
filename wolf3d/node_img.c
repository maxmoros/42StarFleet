/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:39:57 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 19:17:58 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_img	*new_img(t_wolf *node)
{
	t_img	*img;

	if (!(img = (t_img*)ft_memalloc(sizeof(t_img))))
		return (NULL);
	node->img = img;
	node->img->ptr = mlx_new_image(node->mlx, RESX, RESY);
	node->img->img = (int*)mlx_get_data_addr(node->img->ptr, &node->img->bits,
										&node->img->line, &node->img->endian);
	printf("initializing t_img\n");
//	init_img(node);
	return (img);
}

void	init_img(t_wolf *node)
{
	ft_bzero(node->img, sizeof(t_img));
}

void	pixel_to_img(t_wolf *node, int x, int y, int colour)
{
	node->img->img[x + y * node->img->line / sizeof(int)] = colour;
}

void	free_img(t_wolf *node)
{
	if (node)
	{
		if (node->img)
		{
			if (node->img->ptr)
				mlx_destroy_image(node->mlx, node->img->ptr);
			free(node->img);
		}
	}
}
