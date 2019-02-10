/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:21 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:21 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*take(int player_id, void *args)
{
	char		*obj_to_take;

	obj_to_take = (char*)args;
	if (attempt_to_take(player_id, obj_to_take))
	{
		return (ko_response());
	}
	return (ok_response());
}
