/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:56 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:56 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_list_type.h"
#include "client_type.h"
#include "player_type.h"

static void		ply_pop_command(t_command_list **popped_head,
		t_ply_cmd_queue *cmd_queue)
{
	t_command_list	*popped_tail;

	if (*popped_head)
	{
		popped_tail = *popped_head;
		while (popped_tail->next)
			popped_tail = popped_tail->next;
		popped_tail->next = ply_dequeue_command(cmd_queue);
	}
	else
	{
		*popped_head = ply_dequeue_command(cmd_queue);
	}
}

t_command_list	*dequeue_commands(void)
{
	t_command_list	*popped_cmds;
	t_client		*c;

	popped_cmds = NULL;
	while ((c = iter_clients(ACTIVE_PLAYER)))
		while (c->cmdqueue.dequeue_timer == 0)
			ply_pop_command(&popped_cmds, &(c->cmdqueue));
	return (popped_cmds);
}
