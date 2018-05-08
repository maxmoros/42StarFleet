/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:57:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/07 20:34:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mlx(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (!(window = mlx_new_window(mlx, 600, 600, "WOLF3D")))
		ft_putstr("Failed to make MLX window\n");
	else
		ft_putstr("MLX window created\n");
	mlx_string_put(mlx, window, 10, 10, 0x00FF0000, "MAX");
	mlx_loop(mlx);
}

void	wolf3d(int x, int y)
{
	t_map	*map;

	map = new_map(x, y);
	print_map(map);
	mlx();
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_isint(av[1]) && ft_isint(av[2]))
	{
		wolf3d(ft_atoi(av[1]), ft_atoi(av[2]));
	}
	else
		mlx();
	return (0);
}
