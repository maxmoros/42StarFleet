/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:57:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/08 12:44:28 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>
#include <stdlib.h>

int		move(int keycode, t_wolf *node)
{
	mlx_string_put(node->mlx, node->window, 40, 40, 0x00FF0000, "MAX");
	if (keycode)
		;
	return (1);
}

int		key_pressed(int key, t_wolf *node)
{
	int		r;

	ft_putnbr(key);
	ft_putstr(" pressed\n");
	srand(time(NULL));
	r = rand();
	mlx_string_put(node->mlx, node->window, r % 500, r % 500, 0xFF0000, "2");
	if (key || node)
		;
	return (1);
}

int		key_released(int key, t_wolf *node)
{
	int		rx;
	int		ry;

	ft_putnbr(key);
	ft_putstr(" released\n");
	srand(time(NULL));
	rx = rand();
	srand(time(NULL));
	ry = rand();
	mlx_string_put(node->mlx, node->window, rx % 500, ry % 500, 0xFF0000, "2");
	if (key || node)
		;
	return (1);
}

void	mlx(t_wolf *node)
{
	mlx_string_put(node->mlx, node->window, 10, 10, 0x00FF0000, "MAX");
	mlx_hook(node->window, 2, 0x1, key_pressed, node);
	mlx_hook(node->window, 3, 0x1, key_released, node);
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
