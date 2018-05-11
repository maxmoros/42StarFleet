/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:39:57 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 18:01:46 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_img	*new_img(t_wolf *node)
{
	t_img	*img;

	if (!(img = (t_img*)ft_memalloc(sizeof(t_img))))
		return (NULL);
	init_img(node);
	return (img);
}

void	init_img(t_wolf *node)
{
	ft_bzero(node->img, sizeof(t_img));
	node->img->ptr = mlx_new_image(node->mlx, RESX, RESY);
	node->img->img = (int*)mlx_get_data_addr(node->img->ptr, &node->img->bits,
										&node->img->line, &node->img->endian);
}

void	pix_img