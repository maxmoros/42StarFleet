/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:16 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:16 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"

t_client			*g_clients[MAX_CLIENTS + 1] = { 0 };
int					g_count_clients = 0;

void				register_client(int sock_fd, int id, int type)
{
	if (g_count_clients == MAX_CLIENTS)
		FATAL("rewrite clients_lookup.c before making that many clients.");
	g_clients[g_count_clients] = new_client(sock_fd, id, type);
	++g_count_clients;
	socket_lookup_remove(sock_fd, 0);
	socket_lookup_add(sock_fd, type);
}

t_client			*get_client_by_id(int id)
{
	int		i;

	i = 0;
	while (i < g_count_clients)
	{
		assert(g_clients[i]);
		if (g_clients[i]->id == id)
			return (g_clients[i]);
		++i;
	}
	return (NULL);
}

t_client			*get_client_by_socket_fd(int sock_fd)
{
	int		i;

	i = 0;
	while (i < g_count_clients)
	{
		assert(g_clients[i]);
		if (g_clients[i]->socket_fd == sock_fd)
			return (g_clients[i]);
		++i;
	}
	return (NULL);
}

void				unregister_client_by_id(int id)
{
	int			i;
	t_client	*c;
	t_client	*last_in_array;

	i = 0;
	while (i < g_count_clients)
	{
		assert(g_clients[i]);
		if (g_clients[i]->id == id)
		{
			c = g_clients[i];
			socket_lookup_remove(c->socket_fd, 1);
			last_in_array = g_clients[g_count_clients - 1];
			g_clients[i] = last_in_array;
			g_clients[g_count_clients - 1] = NULL;
			free(c);
			--g_count_clients;
			return ;
		}
		++i;
	}
}
