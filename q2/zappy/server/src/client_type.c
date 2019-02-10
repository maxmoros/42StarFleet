/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:14 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:14 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"

t_client	*new_client(int socket_fd, int id, int type)
{
	t_client		*c;

	if (!(c = malloc(sizeof(*c))))
		return (NULL);
	ply_new_cmdqueue(&(c->cmdqueue));
	c->socket_fd = socket_fd;
	c->type = type;
	c->id = id;
	return (c);
}
