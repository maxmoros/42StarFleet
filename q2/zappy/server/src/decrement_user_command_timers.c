/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrement_user_command_timers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:33 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:33 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"
#include "command_player_queue_type.h"

void	decrement_user_command_timers(void)
{
	t_client	*c;

	while ((c = iter_clients(ACTIVE_PLAYER)))
	{
		if (c->cmdqueue.dequeue_timer > 0)
			c->cmdqueue.dequeue_timer -= 1;
	}
}
