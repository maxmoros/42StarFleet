/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:18 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:18 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_TYPE_H
# define TILE_TYPE_H
# include "server.h"

struct	s_tile
{
	t_player			**players;
	int					parray_size;
	int					x;
	int					y;
	int					eggs;
	t_objcount			count;
};

#endif
