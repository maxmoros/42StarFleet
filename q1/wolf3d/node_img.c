/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:39:57 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/30 19:40:50 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_img	*new_img(t_wolf *node, char tex, char *filename)
{
	t_img	*img;

	if (!(img = (t_img*)ft_memalloc(sizeof(t_img))))
		return (NULL);
	node->img = img;
	if (tex)
		node->img->ptr = mlx_xpm_file_to_image(node->mlx, filename,
													&img->x, &img->y);
	else
		node->img->ptr = mlx_new_image(node->mlx, RESX, RESY);
	node->img->img = (int*)mlx_get_data_addr(node->img->ptr, &node->img->bits,
										&node->img->line, &node->img->endian);
	ft_putstr("\tt_img successful\n");
	return (img);
}

void	init_img(t_wolf *node)
{
	ft_bzero(node->img, sizeof(t_img));
}

void	pixel_to_img(t_img *img, int x, int y, int colour)
{
	img->img[x + y * img->line / sizeof(int)] = colour;
}

int		img_to_pixel(t_img *img, int x, int y)
{
	return (img->img[x + y * img->line / sizeof(int)]);
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
