/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:57:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/08 10:11:00 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		move(int keycode, t_wolf_inst *node)
{
	mlx_string_put(node->mlx, node->window, 40, 40, 0x00FF0000, "MAX");
	if (keycode)
		;
	return (1);
}

void	mlx(t_wolf_inst *node)
{
	node->mlx = mlx_init();
	if (!(node->window = mlx_new_window(node->mlx, 600, 600, "WOLF3D")))
		ft_putstr("Failed to make MLX window\n");
	else
		ft_putstr("MLX window created\n");
	mlx_string_put(node->mlx, node->window, 10, 10, 0x00FF0000, "MAX");
	mlx_key_hook(node->window, move, node);
	mlx_loop(node->mlx);
}

void	wolf3d(int x, int y)
{
	t_wolf_inst		*node;

	node = new_wolf_inst(x, y, 600, 600);
	print_map(node->map);
	mlx(node);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_isint(av[1]) && ft_isint(av[2]))
		wolf3d(ft_atoi(av[1]), ft_atoi(av[2]));
	return (0);
}
