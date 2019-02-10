/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_event_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:32 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:32 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "client_type.h"

void		gfx_sendone(int fd, char *format, ...)
{
	char	*buf;
	int		len;
	va_list	args;

	va_start(args, format);
	len = vasprintf(&buf, format, args);
	send(fd, buf, len, 0);
	free(buf);
	va_end(args);
}

void		gfx_sendall(char *format, ...)
{
	t_client	*c;
	va_list		args;
	int			len;
	char		*buf;

	va_start(args, format);
	len = vasprintf(&buf, format, args);
	while ((c = iter_clients(GFX)))
		send(c->socket_fd, buf, len, 0);
	free(buf);
	va_end(args);
}
