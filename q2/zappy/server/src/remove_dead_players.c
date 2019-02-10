/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dead_players.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:41 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:41 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"

void	send_death_message(int sock_fd)
{
	if (send(sock_fd, SERVER_STRING_DEATH, strlen(SERVER_STRING_DEATH), 0) <= 0)
		perror("send death message");
}

void	remove_dead_players(void)
{
	int			*player_ids;
	int			pid_count;
	t_client	*client;
	int			i;

	player_ids = kill_and_return_dead_players(&pid_count);
	i = 0;
	while (i < pid_count)
	{
		gfx_sendall("DEATH %d\n", player_ids[i]);
		if ((client = get_client_by_id(player_ids[i])))
		{
			send_death_message(client->socket_fd);
			unregister_client_by_id(player_ids[i]);
		}
		++i;
	}
}
