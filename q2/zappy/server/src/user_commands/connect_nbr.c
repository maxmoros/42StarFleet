/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:31 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:31 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*connect_nbr(int player_id, void *args)
{
	char		*res;

	(void)args;
	asprintf(&res, "%d\n", get_team_open_slots_by_pid(player_id));
	return (res);
}
