/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:52:58 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/15 20:41:29 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void	grim_print(char ***map, int *xy)
{
	int	x;
	int y;

	ft_putstr(map[0][1]);
	ft_putchar('\n');
	y = -1;
	while ((x = -1) && ++y < xy[1])
	{
		while (++x < xy[0])
		{
			if (map[1][y][x] == 'x')
				ft_putchar(map[0][0][0]);
			else if (map[1][y][x] == 'o')
				ft_putchar(map[0][0][2]);
			else if (map[1][y][x] == '1')
				ft_putchar(map[0][0][3]);
			else if (map[1][y][x] == '2')
				ft_putchar(map[0][0][4]);
			else
				ft_putchar(map[0][0][1]);
		}
		ft_putchar('\n');
	}
}

void	grim_results(int *xy)
{
	ft_putstr("RESULT IN ");
	ft_putnbr(xy[6]);
	ft_putstr(" STEPS!\n");
}

int		grim_close(char ***map, int *xy, int out, int mapset)
{
	if (map)
	{
		if (mapset)
		{
			while (xy[1]-- > 0)
				free(map[1][xy[1]]);
			free(map[1]);
		}
		if (map[0])
		{
			if (map[0][0])
				free(map[0][0]);
			if (map[0][1])
				free(map[0][1]);
			free(map[0]);
		}
		free(map);
	}
	close(xy[7]);
	free(xy);
	return (out);
}

int		grim(char *input)
{
	char	***map;
	int		*xy;

	map = NULL;
	if (!(xy = (int*)ft_memalloc(sizeof(int) * 8)))
		return (0);
	if (!input)
		xy[7] = 0;
	else if (!(xy[7] = open(input, O_RDONLY)))
		return (0);
	if (!(map = grim_init(xy)))
		return (0);
	if (!grim_solve(map, xy))
		return (grim_close(map, xy, 0, 1));
	grim_print(map, xy);
	grim_results(xy);
	return (grim_close(map, xy, 1, 1));
}

int		main(int ac, char **av)
{
	int		i;

	if (ac > 1)
	{
		i = 0;
		while (++i < ac)
			if (!grim(av[i]))
				ft_putstr("MAP ERROR\n");
	}
	else if (!grim(NULL))
		ft_putstr("MAP ERROR\n");
	return (0);
}
