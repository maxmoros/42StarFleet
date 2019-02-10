/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:45 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:45 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_list_type.h"
#include "command_type.h"

void	execute_command_list(t_command_list *list)
{
	while (list)
	{
		list->cmd->response = list->cmd->cmdfunc(list->cmd->player_id,
				list->cmd->args);
		list = list->next;
	}
}
