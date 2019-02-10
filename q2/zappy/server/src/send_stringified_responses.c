/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_stringified_responses.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:36 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:36 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_list_type.h"
#include "command_type.h"
#include "client_type.h"

void	send_stringified_responses(t_command_list *lst)
{
	t_client	*client;
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->cmd;
		client = get_client_by_id(cmd->player_id);
		assert(client != NULL);
		if (send(client->socket_fd, cmd->response,
					strlen(cmd->response), 0) <= 0)
			perror("send stringified response");
		lst = lst->next;
	}
}
