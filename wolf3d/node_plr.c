/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:03:15 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/07 21:32:32 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_plr	*new_player(void)
{
	t_plr	*player;

	if (!(player = (t_plr*)ft_memalloc(sizeof(t_plr))))
		return (NULL);
	player->pos[0] = 1;
	player->pos[1] = 1;
	player->dir[0] = 1;
	player->dir[1] = 0;
	player->pln[0] = 0;
	player->pln[1] = 0.66;
	return (player);
}

void	free_player(t_plr *player)
{
	if (player)
		free(player);
}
