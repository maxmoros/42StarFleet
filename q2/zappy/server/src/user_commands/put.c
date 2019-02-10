/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:24 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:24 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*put(int player_id, void *args)
{
	char		*obj_to_put;

	obj_to_put = (char*)args;
	if (attempt_to_put(player_id, obj_to_put))
	{
		return (ko_response());
	}
	return (ok_response());
}
