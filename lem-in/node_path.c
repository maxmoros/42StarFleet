#include "lem_in.h"

t_path  *new_path(t_path *next, t_path *copy, t_room *room, int next)
{
	t_path  *node;

	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	node->next = next;
	if (copy)
	{
		node->step = copy->step;
		node->crumbs = ft_strdup(copy->crumbs);
		node->crumbs[next] = 1;
	}
	else 
	{
		if (!(node->crumbs = (char*)ft_memalloc(g_lem.room_count + 1)))
			return (0);
		node->crumbs[0] = 1;
		node->steps = 0;
	}
	return (node);
}
