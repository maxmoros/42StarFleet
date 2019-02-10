/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:11 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:11 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

/*
** Removes the player from their current tile and places them on
** the adjacent tile in the direction specified by [ dir ]
**
** Common usage: move_player(p, p->facing);
*/

int			move_player(t_player *p, int dir)
{
	t_tile		*next;

	next = get_adj_tile(p->tile, dir);
	remove_player_from_tile(p, p->tile);
	add_player_to_tile(p, next);
	p->tile = next;
	return (0);
}
