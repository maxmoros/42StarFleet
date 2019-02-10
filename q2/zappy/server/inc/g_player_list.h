/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_player_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:30 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:30 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_PLAYER_LIST_H
# define G_PLAYER_LIST_H

# include "server.h"
# include "player_type.h"

# define START_SIZE 64

t_player	**g_player_list;
int			g_list_size;

#endif
