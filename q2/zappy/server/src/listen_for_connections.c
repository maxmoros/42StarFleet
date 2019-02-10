/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_for_connections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:48 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:48 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"

static int	g_server_fd = -1;

inline int	get_server_fd(void)
{
	return (g_server_fd);
}

void		increase_rlimit(void)
{
	struct rlimit rl;

	getrlimit(RLIMIT_NOFILE, &rl);
	rl.rlim_cur = OPEN_MAX;
	setrlimit(RLIMIT_NOFILE, &rl);
}

void		listen_for_connections(int port)
{
	struct sockaddr_in	server;
	socklen_t			len;
	int					fd;
	int					optval;

	increase_rlimit();
	optval = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0)
		ERR_OUT("socket");
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		ERR_OUT("setsockopt");
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1)
		ERR_OUT("bind");
	len = sizeof(server);
	if (getsockname(fd, (struct sockaddr *)&server, &len) == -1)
		ERR_OUT("getsockname");
	optval = 1;
	if (listen(fd, 3) == -1)
		ERR_OUT("listen");
	g_server_fd = fd;
	socket_lookup_add(fd, SERVER);
}

void		handle_incoming_socket_data(void)
{
	int		fd;

	while ((fd = iter_next_readable_socket()) != -1)
	{
		if (fd == get_server_fd())
			initiate_handshake(fd);
		else if (socket_lookup_has(fd, HANDSHAKE))
			complete_handshake(fd);
		else if (socket_lookup_has(fd, GFX))
		{
			fprintf(stderr, "received unhandled message \
from GFX client; closing connection\n");
			unregister_client_by_id(get_client_by_socket_fd(fd)->id);
		}
		else
		{
			assert(socket_lookup_has(fd, ACTIVE_PLAYER));
			receive_user_message(fd);
		}
	}
}
