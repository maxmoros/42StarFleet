/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:11:03 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/30 17:06:25 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>			//###

# define			START	0x01
# define			END		0x02
# define			PATH	0x04

typedef struct		s_room
{
	char			*name;
	struct s_room	*next;
	char			*adjc;
	int				x;
	int				y;
	struct s_room	*prev;
}					t_room;

typedef struct		s_path
{
	int				step;
	struct s_path	*next;
	struct s_path	*list;
	struct t_room	*room;
}					t_path;

/*
**Global Lem-INstance variable holder ;)
**	rooms - pointer to list of rooms, beginning with START
**	paths - pointer to list of possible non overlapping paths.
**			begins with shortest.
**	ants  - number of ants.
**	check - Bit switch for complete input verification,
**			0x1 : has START
**			0x2 : has END
**			0x4 : has path
*/

typedef struct		s_lem
{
	struct s_room	*rooms;
	struct s_path	*paths;
	char			*occupied;
	int				room_count;
	int				ants;
	char			check;
}					t_lem;

extern t_lem		g_lem;

/*
**Read/Verify input and build rooms.
*/

int					get_ants();
int					build_map();

t_room				*line_room(char *line, t_room *next);
int					valid_name(char *name);
int					count_rooms();
void				print_rooms();



/*
**Connect all rooms via tube list.
*/

#endif