/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_lookup.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:24 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:24 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_LOOKUP_H
# define CLIENTS_LOOKUP_H
# include "server.h"
# include "client_type.h"

extern t_client		*g_clients[MAX_CLIENTS + 1];
extern int			g_count_clients;

#endif
