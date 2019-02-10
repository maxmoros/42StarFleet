/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:26 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:26 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_TYPE_H
# define PLAYER_TYPE_H
# include "server.h"

struct	s_player
{
	t_tile				*tile;
	int					facing;
	int					energy;
	int					level;
	int					id;
	int					team_id;
	t_objcount			count;
};

#endif
