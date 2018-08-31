/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:03:15 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/30 19:43:58 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	find_pos(t_map *map, t_plr *player)
{
	int		x;
	int		y;

	x = -1;
	while (++x < map->dim[0])
	{
		y = -1;
		while (++y < map->dim[1])
			if (map->xy[x][y] == '0')
			{
				player->pos[0] = x;
				player->pos[1] = y;
				return (1);
			}
	}
	return (0);
}

t_plr		*new_player(t_wolf *node)
{
	t_plr	*player;

	if (!(player = (t_plr*)ft_memalloc(sizeof(t_plr))))
		return (NULL);
	player->theta = 45;
	player->dir[0] = 1;
	player->dir[1] = 0;
	player->pln[0] = 0;
	player->pln[1] = 0.66;
	player->z = 0;
	if (find_pos(node->map, player))
		return (player);
	ft_putstr("No valid player placement\n");
	return (free_wolf_inst(node, NULL));
}

void		rotate_player(t_wolf *node)
{
	double	rad;

	node->plr->theta -= (node->io->a ? 1 : 0);
	node->plr->theta += (node->io->d ? 1 : 0);
	rad = (double)(node->plr->theta % 360) / 180.0 * M_PI;
	node->plr->dir[0] = cos(rad);
	node->plr->dir[1] = sin(rad);
	node->plr->pln[0] = 0.66 * cos(rad + M_PI / 2);
	node->plr->pln[1] = 0.66 * sin(rad + M_PI / 2);
}

void		move_player(t_wolf *node)
{
	double	tmpx;
	double	tmpy;

	tmpx = (node->io->w ? DELTA * node->plr->dir[0] : 0);
	tmpy = (node->io->w ? DELTA * node->plr->dir[1] : 0);
	tmpx -= (node->io->s ? DELTA * node->plr->dir[0] : 0);
	tmpy -= (node->io->s ? DELTA * node->plr->dir[1] : 0);
	tmpx += (node->io->q ? DELTA * node->plr->dir[1] : 0);
	tmpy -= (node->io->q ? DELTA * node->plr->dir[0] : 0);
	tmpx -= (node->io->e ? DELTA * node->plr->dir[1] : 0);
	tmpy += (node->io->e ? DELTA * node->plr->dir[0] : 0);
	if (POSINMAP(node, 1, tmpy) && MAPBLCK(node, 0.0, tmpy) == '0')
		node->plr->pos[1] += tmpy;
	if (POSINMAP(node, 0, tmpx) && MAPBLCK(node, tmpx, 0.0) == '0')
		node->plr->pos[0] += tmpx;
	node->plr->z += (node->io->space && node->plr->z < 0.46 ? 0.05 : 0);
	node->plr->z -= (!node->io->space && node->plr->z > 0.01 ? 0.05 : 0);
	rotate_player(node);
}

void		free_player(t_plr *player)
{
	player ? free(player) : NULL;
}
