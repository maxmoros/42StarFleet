#ifndef LEM-IN_H
# define LEM-IN_H

# include "libft/libft.h"

# define			START	0x01
# define			END		0x02

typedef struct		s_room
{
	char			*name;
	struct s_room	*next;
	struct s_room	**tube;
	int				x;
	int				y;
	struct s_room	*prev;
}					t_room;

typedef struct		s_path
{
	int				step;
	struct s_path	*next;
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
*/

typedef struct		s_lem
{
	struct s_room	*rooms;
	struct s_path	*paths;
	int				ants;
	char			check;
}					t_lem;

extern t_lem		g_lem;

/*
**Read/Verify input and build rooms.
*/

int					get_ants();

/*
**Connect all rooms via tube list.
*/
