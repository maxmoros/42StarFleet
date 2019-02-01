#include "lem_in.h"

t_path  *new_path(t_path *next, t_room *room, int steps)
{
	t_path  *node;

	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	node->room = room;
	node->steps = steps;
	return (node);
}

t_room	*get_room(int index)
{
	t_room	*node;

	node = g_lem.rooms;
	while (index-- && node->next)
		node = node->next;
	return (node);
}

void	advance_paths(t_path *start)
{
	t_path	*node;
	int		i;

	node = start;
	while (node)
	{
		i = -1;
		while (++i < g_lem.room_count)
		{
			
		}
	}
}

t_path	*find_path(void)
{
	t_path	*node;

	node = new_path(NULL, get_room(g_lem.room_count - 1), 0);
	g_lem.paths = node;
	advance_paths(node);
}
