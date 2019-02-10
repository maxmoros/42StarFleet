/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_player_queue_type.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:31 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:31 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PLAYER_QUEUE_TYPE_H
# define COMMAND_PLAYER_QUEUE_TYPE_H
# include "server.h"
# include "command_list_type.h"

struct	s_ply_cmd_queue
{
	t_command_list	*jobs[10];
	int				head_ind;
	int				size;
	int				dequeue_timer;
};

#endif
