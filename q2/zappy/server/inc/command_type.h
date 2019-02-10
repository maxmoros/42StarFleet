/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:19 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:19 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TYPE_H
# define COMMAND_TYPE_H
# include "server.h"

struct	s_command
{
	t_cmdfunc	cmdfunc;
	char		*args;
	char		*response;
	int			player_id;
};

#endif
