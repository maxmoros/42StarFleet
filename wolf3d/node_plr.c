/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:03:15 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 20:16:21 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "math.h"

t_plr	*new_player(void)
{
	t_plr	*player;

	if (!(player = (t_plr*)ft_memalloc(sizeof(t_plr))))
		return (NULL);
	player->pos[0] = 2;
	player->pos[1] = 2;
	player->theta = 0;
	player->dir[0] = 1;
	player->dir[1] = 0;
	player->pln[0] = 0;
	player->pln[1] = 0.66;
	return (player);
}

void	move_player(t_wolf *node)
{
	double	delta;
	double	rad;
	double	tmpx;
	double	tmpy;

	delta = 0.04;
	tmpx = (node->io->w ? delta * node->plr->dir[0] : 0);
	tmpy = (node->io->w ? delta * node->plr->dir[1] : 0);
	tmpx -= (node->io->s ? delta * node->plr->dir[0] : 0);
	tmpy -= (node->io->s ? delta * node->plr->dir[1] : 0);
	if (node->plr->pos[0] + tmpx > 0.0 && node->plr->pos[1] + tmpy > 0.0 &&
			node->plr->pos[0] + tmpx < node->map->dim[0] &&
			node->plr->pos[1] + tmpy < node->map->dim[1] &&
			(node->map->xy[(int)(node->plr->pos[0] + tmpx)]
			[(int)(node->plr->pos[1] + tmpy)] == '0'))
	{
		node->plr->pos[0] += tmpx;
		node->plr->pos[1] += tmpy;
	}
	node->plr->theta -= (node->io->a ? 1 : 0);
	node->plr->theta += (node->io->d ? 1 : 0);
	rad = (double)(node->plr->theta % 360) / 180.0 * M_PI;
	node->plr->dir[0] = cos(rad);
	node->plr->dir[1] = sin(rad);
	node->plr->pln[0] = 0.66 * cos(rad + M_PI / 2);
	node->plr->pln[1] = 0.66 * sin(rad + M_PI / 2);
}

int		print_player(t_plr *player)
{
	printf("player at (%f, %f), dir (%f, %f), theta = %d, pln (%f, %f)\n",
	player->pos[0], player->pos[1], player->dir[0], player->dir[1],
	player->theta, player->pln[0], player->pln[1]);
	return (0);
}

void	free_player(t_plr *player)
{
	if (player)
		free(player);
}
