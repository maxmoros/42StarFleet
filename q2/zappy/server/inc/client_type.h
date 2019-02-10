/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:28 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:28 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_TYPE_H
# define CLIENT_TYPE_H
# include "server.h"
# include "command_player_queue_type.h"

struct	s_client
{
	int					socket_fd;
	int					id;
	int					type;
	t_ply_cmd_queue		cmdqueue;
};

#endif
