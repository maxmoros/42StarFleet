/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:28 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:28 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

char	*left(int player_id, void *args)
{
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	p->facing = direction_add(p->facing, WEST);
	gfx_sendall("LEFT %d\n", player_id);
	return (ok_response());
}

char	*right(int player_id, void *args)
{
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	p->facing = direction_add(p->facing, EAST);
	gfx_sendall("RIGHT %d\n", player_id);
	return (ok_response());
}
