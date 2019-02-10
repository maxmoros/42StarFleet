/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_socket_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:35 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:35 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static fd_set	g_handshake_fds;
static fd_set	g_active_player_fds;
static fd_set	g_gfx_fds;
static fd_set	g_all_fds;
static int		g_max_fd = 0;
static int		g_prev_iter = -1;

void	socket_lookup_init(int do_close)
{
	int i;

	if (do_close == 1)
	{
		i = 0;
		while (i <= g_max_fd)
		{
			if (FD_ISSET(i, &g_all_fds))
				close(i);
			++i;
		}
	}
	FD_ZERO(&g_handshake_fds);
	FD_ZERO(&g_active_player_fds);
	FD_ZERO(&g_all_fds);
	FD_ZERO(&g_gfx_fds);
	g_max_fd = 0;
	g_prev_iter = -1;
}

void	socket_lookup_add(int fd, enum e_socktype type)
{
	static int is_first_entry = 1;

	if (is_first_entry)
	{
		socket_lookup_init(0);
		is_first_entry = 0;
	}
	if (type == ACTIVE_PLAYER)
		FD_SET(fd, &g_active_player_fds);
	else if (type == HANDSHAKE)
		FD_SET(fd, &g_handshake_fds);
	else if (type == GFX)
		FD_SET(fd, &g_gfx_fds);
	FD_SET(fd, &g_all_fds);
	if (fd > g_max_fd)
		g_max_fd = fd;
}

void	socket_lookup_remove(int fd, int do_close)
{
	int		new_max_fd;

	FD_CLR(fd, &g_active_player_fds);
	FD_CLR(fd, &g_handshake_fds);
	FD_CLR(fd, &g_gfx_fds);
	FD_CLR(fd, &g_all_fds);
	if (g_max_fd == fd)
	{
		new_max_fd = g_max_fd - 1;
		while (!(FD_ISSET(new_max_fd, &g_all_fds)))
		{
			--new_max_fd;
			assert(new_max_fd > 0);
		}
		g_max_fd = new_max_fd;
	}
	if (do_close)
		close(fd);
}

int		socket_lookup_has(int fd, enum e_socktype type)
{
	if (type == ACTIVE_PLAYER)
		return (FD_ISSET(fd, &g_active_player_fds));
	if (type == HANDSHAKE)
		return (FD_ISSET(fd, &g_handshake_fds));
	if (type == GFX)
		return (FD_ISSET(fd, &g_gfx_fds));
	return (0);
}

int		iter_next_readable_socket(void)
{
	static fd_set	readable;
	struct timeval	timeout;
	int				curr;

	if (g_prev_iter == -1)
	{
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		readable = g_all_fds;
		select(g_max_fd + 1, &readable, NULL, NULL, &timeout);
	}
	curr = g_prev_iter + 1;
	while (curr <= g_max_fd && !(FD_ISSET(curr, &readable)))
		++curr;
	if (curr > g_max_fd)
		curr = -1;
	g_prev_iter = curr;
	return (curr);
}
