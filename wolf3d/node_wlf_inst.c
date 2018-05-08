/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_wlf_inst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:07:01 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/07 21:31:35 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d"

t_wolf_inst	*new_wolf_inst(int x, int y, unsigned int resx, unsigned int resy)
{
	t_wolf_inst		*node;

	if (!(node = (t_wolf_inst*)ft_memalloc(sizeof(t_wolf_inst))))
		return (NULL);
	if (!(node->map = new_map(x, y)) ||
		!(node->plr = new_player()) ||
		!(node->ray = new_ray()) ||
		!(node->mlx = mlx_init()) ||
		!(node->window = mlx_new_window(node->mlx, resx, resy, "WOLF3D")))
		//Do I need diferent name for multiple windows?
		return (free_wolf_inst(node, 0));
}

long		free_wolf_inst(t_wolf_inst *node, long out)
{
	if (node)
	{
		if (node->map)
			free_map(node->map, 0);
		if (node->plr)
			free_player(node->plr);
		if (node->ray)
			free_ray(node->ray);
		if (node->window)
			mlx_destroy_window(node->window);
		//Do I need to free mlx?
	}
	return (out);
}