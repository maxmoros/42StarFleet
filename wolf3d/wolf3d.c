/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:57:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 10:58:43 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>
#include <stdlib.h>

int		key_pressed(int key, t_wolf *node)
{
	ft_putnbr(key);
	ft_putstr(" pressed\n");
	if (key == 0)
		node->io->a = 1;
	else if (key == 1)
		node->io->s = 1;
	else if (key == 2)
		node->io->d = 1;
	else if (key == 13)
		node->io->w = 1;
	else if (key == 49)
		node->io->space = 1;
	else if (key == 53)
		;		//Close program
	return (1);
}

int		key_released(int key, t_wolf *node)
{
	ft_putnbr(key);
	ft_putstr(" released\n");
	if (key == 0)
		node->io->a = 0;
	else if (key == 1)
		node->io->s = 0;
	else if (key == 2)
		node->io->d = 0;
	else if (key == 13)
		node->io->w = 0;
	else if (key == 49)
		node->io->space = 0;
	return (1);
}

void	mlx(t_wolf *node)
{
	mlx_string_put(node->mlx, node->window, 10, 10, 0x00FF0000, "MAX");
	mlx_hook(node->window, 2, 0x1, key_pressed, node);
	mlx_hook(node->window, 3, 0x1, key_released, node);
	mlx_loop_hook(node->mlx, geng, node);
	mlx_loop(node->mlx);
}

void	wolf3d(int x, int y)
{
	t_wolf		*node;

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
