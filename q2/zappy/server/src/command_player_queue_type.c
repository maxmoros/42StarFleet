/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_player_queue_type.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:51 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:51 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_type.h"
#include "command_list_type.h"
#include "command_player_queue_type.h"
#define MOVE_FIRST(x) ((x + 10) % 10)

void				ply_new_cmdqueue(t_ply_cmd_queue *q)
{
	int			i;

	i = -1;
	q->head_ind = 0;
	while (++i < 10)
		q->jobs[i] = NULL;
	q->size = 0;
	q->dequeue_timer = -1;
}

int					ply_enqueue_command(t_ply_cmd_queue *q, t_command *cmd)
{
	if (!q || q->size >= MAX_COMMANDS)
		return (-1);
	else
	{
		if (!cmd)
			return (-1);
		q->jobs[MOVE_FIRST(q->size + q->head_ind)] = new_cmdlist(cmd);
		q->jobs[MOVE_FIRST(q->size + q->head_ind)]->next = NULL;
		if (q->size <= 0)
			q->dequeue_timer =
				get_cmdfunc_tick_delay(q->jobs[q->head_ind]->cmd->cmdfunc);
		q->size++;
	}
	return (0);
}

int					ply_enqueue_front(t_ply_cmd_queue *q, t_command *cmd)
{
	if (!q || q->size >= MAX_COMMANDS)
		return (-1);
	else
	{
		if (!cmd)
			return (-1);
		q->head_ind = MOVE_FIRST(q->head_ind - 1);
		q->jobs[MOVE_FIRST(q->head_ind)] = new_cmdlist(cmd);
		q->jobs[MOVE_FIRST(q->head_ind)]->next = NULL;
		q->size++;
		q->dequeue_timer =
			get_cmdfunc_tick_delay(q->jobs[q->head_ind]->cmd->cmdfunc);
	}
	return (0);
}

t_command_list		*ply_dequeue_command(t_ply_cmd_queue *q)
{
	t_command_list	*temp;

	temp = NULL;
	if (!q)
		return (NULL);
	if (q->size != 0)
	{
		temp = q->jobs[q->head_ind];
		q->jobs[q->head_ind] = NULL;
		q->head_ind = MOVE_FIRST(q->head_ind + 1);
		q->size--;
		if (q->size > 0)
			q->dequeue_timer =
				get_cmdfunc_tick_delay(q->jobs[q->head_ind]->cmd->cmdfunc);
		else
			q->dequeue_timer = -1;
		return (temp);
	}
	else
		return (NULL);
}
