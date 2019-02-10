/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data_api_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:02 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:02 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "g_player_list.h"

int		delete_player_from_list(t_player *p)
{
	int	pid;

	pid = p->id;
	free(g_player_list[pid]);
	g_player_list[pid] = NULL;
	return (0);
}
