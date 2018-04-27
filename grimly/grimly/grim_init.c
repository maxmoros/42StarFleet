/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 10:28:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/15 20:41:30 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

static int	grim_verify(char ***map, int *xy)
{
	char	start;
	char	finish;
	int		x;
	int		y;

	start = 0;
	finish = 0;
	y = -1;
	while (++y < xy[1] && (x = -1))
		while (++x < xy[0])
		{
			if (map[1][y][x] == map[0][0][0])
				map[1][y][x] = 'x';
			else if (map[1][y][x] == map[0][0][1])
				map[1][y][x] = 0;
			else if (map[1][y][x] == map[0][0][3] && (xy[2] = x) >= 0 &&
					(map[1][y][x] = '1') && (xy[3] += y) >= 0 && start++)
				return (grim_close(map, xy, 0, 1));
			else if (map[1][y][x] == map[0][0][4] && (xy[4] = x) >= 0 &&
					!(map[1][y][x] = 0) && (xy[5] += y) >= 0 && finish++)
				return (grim_close(map, xy, 0, 1));
			else if (map[1][y][x] != '1' && x != xy[4] && y != xy[5])
				return (grim_close(map, xy, 0, 1));
		}
	return (start && finish ? 1 : grim_close(map, xy, 0, 1));
}

static int	grim_map(char ***map, int *xy)
{
	int		i;

	if (!(map[1] = (char**)ft_memalloc(sizeof(char*) * (xy[1] + 1))))
		return (grim_close(NULL, xy, 0, 0));
	map[1][xy[1]] = NULL;
	i = -1;
	while (++i < xy[1])
		if (get_next_line(xy[7], &map[1][i]) < 1 ||
				(int)ft_strlen(map[1][i]) != xy[0])
		{
			while (i >= 0)
				free(map[1][i--]);
			free(map[1]);
			return (grim_close(map, xy, 0, 0));
		}
	return (xy[7] && get_next_line(xy[7], &map[0][1]) ?
			grim_close(map, xy, 0, 1) : 1);
}

static char	*clean_key(char **key, char ***map)
{
	if (ft_isdigit(**key) && !map[0][0][1])
		while (ft_isdigit(**key))
			(*key)++;
	else
		(*key)++;
	return (*key);
}

static int	grim_key(char ***map, int *xy)
{
	char	*key;
	int		i;
	int		j;

	if (get_next_line(xy[7], &map[0][1]) < 1)
		return (grim_close(map, xy, 0, 0));
	key = map[0][1];
	if ((xy[1] = ft_atoi(key)) < 1 || *clean_key(&key, map) != 'x' ||
			(xy[0] = ft_atoi(clean_key(&key, map))) < 1)
		return (grim_close(map, xy, 0, 0));
	i = -1;
	while (++i < 5)
		if ((j = -1) &&
				!(map[0][0][i] = *clean_key(&key, map)))
			return (grim_close(map, xy, 0, 0));
		else
			while (++j < i)
				if (map[0][0][j] == map[0][0][i])
					return (grim_close(map, xy, 0, 0));
	return (*++key ? grim_close(map, xy, 0, 0) : 1);
}

char		***grim_init(int *xy)
{
	char	***map;

	if (!(map = (char***)ft_memalloc(sizeof(char**) * 2)) ||
			!(map[0] = (char**)ft_memalloc(sizeof(char*) * 2)) ||
			!(map[0][0] = (char*)ft_memalloc(sizeof(char) * 5)))
		return (0);
	if (!grim_key(map, xy) || !grim_map(map, xy) ||
			!grim_verify(map, xy))
		return (0);
	return (map);
}
