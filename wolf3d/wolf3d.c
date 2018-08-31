/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:57:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/30 19:21:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_pressed(int key, t_wolf *node)
{
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == 0 || key == 123)
		node->io->a = 1;
	else if (key == 1 || key == 125)
		node->io->s = 1;
	else if (key == 2 || key == 124)
		node->io->d = 1;
	else if (key == 13 || key == 126)
		node->io->w = 1;
	else if (key == 12)
		node->io->q = 1;
	else if (key == 14)
		node->io->e = 1;
	else if (key == 49)
		node->io->space = 1;
	else if (key == 53)
		free_wolf_inst(node, 0);
	return (1);
}

int		key_released(int key, t_wolf *node)
{
	if (key == 0 || key == 123)
		node->io->a = 0;
	else if (key == 1 || key == 125)
		node->io->s = 0;
	else if (key == 2 || key == 124)
		node->io->d = 0;
	else if (key == 13 || key == 126)
		node->io->w = 0;
	else if (key == 12)
		node->io->q = 0;
	else if (key == 14)
		node->io->e = 0;
	else if (key == 49)
		node->io->space = 0;
	return (1);
}

void	mlx(t_wolf *node)
{
	mlx_hook(node->window, 2, 0x1, key_pressed, node);
	mlx_hook(node->window, 3, 0x1, key_released, node);
	mlx_loop_hook(node->mlx, geng, node);
	mlx_hook(node->window, 17, 0, close_wolf, node);
	mlx_loop(node->mlx);
}

void	wolf3d(int x, int y)
{
	t_wolf		*node;

	node = new_wolf_inst(x, y, RESX, RESY);
	ft_putstr("Wolf initialized\n\n");
	print_map(node->map);
	mlx(node);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_isint(av[1]) && ft_isint(av[2]))
		wolf3d(ft_atoi(av[1]), ft_atoi(av[2]));
	else
	{
		ft_putstr("\tUsage1: \"cat MAP_FILE | ./wolf3d X_DIM Y_DIM\"\n");
		ft_putstr("\tUsage2: \"./wolf3d X_DIM Y_DIM\"\n");
		ft_putstr("\t\tManual input [0]:open [1..3]:wall\n");
	}
	return (0);
}
