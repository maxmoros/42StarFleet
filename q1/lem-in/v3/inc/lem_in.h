/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:11:03 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/07 10:45:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START	0x01
# define END	0x02
# define PATH	0x04

typedef struct		s_room
{
	char			*name;
	struct s_room	*next;
	char			*adjc;
	int				x;
	int				y;
}					t_room;

typedef struct		s_path
{
	char			**trail;
	int				length;
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
	struct s_path	**paths;
	char			**map;
	int				occupied;
	int				*x;
	int				*y;
	int				w;
	int				room_count;
	int				ants;
	char			check;
}					t_lem;

extern t_lem		g_lem;

void				init_lem(void);
void				exit_lem(char *error);
int					get_ants(void);
int					build_map(void);

t_room				*line_room(char *line, t_room *next);
int					valid_name(char *name);
int					count_rooms(void);
void				print_rooms(void);
t_room				*get_room(int index);
int					build_logic_map(void);
int					traverse_map(void);
void				map_path(void);
void				move_ants(void);
int					free_ret(char *line, int ret);

#endif
