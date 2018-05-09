/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_wolf_inst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:07:01 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 10:54:42 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf		*new_wolf_inst(int x, int y, unsigned int resx, unsigned int resy)
{
	t_wolf		*node;

	if (!(node = (t_wolf*)ft_memalloc(sizeof(t_wolf))))
		return (NULL);
	if (!(node->map = new_map(x, y)) ||
		!(node->plr = new_player()) ||
		!(node->ray = new_ray()) ||
		!(node->io = new_io()) ||
		!(node->mlx = mlx_init()) ||
		!(node->window = mlx_new_window(node->mlx, resx, resy, "WOLF3D")))
		return (free_wolf_inst(node, NULL));
	return (node);
}

void	*free_wolf_inst(t_wolf *node, void *out)
{
	if (node)
	{
		if (node->map)
			free_map(node->map, 0);
		if (node->plr)
			free_player(node->plr);
		if (node->ray)
			free_ray(node->ray);
		if (node->io)
			free_io(node->io);
		if (node->window)
			mlx_destroy_window(node->mlx, node->window);
		else if (node->mlx)
			mlx_destroy_window(node->mlx, NULL);
	}
	return (out);
}
