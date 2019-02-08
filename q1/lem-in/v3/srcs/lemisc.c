#include <lem_in.h>

t_room			*get_room(int index)
{
	t_room	*room;

	if (index < 0 || index >= g_lem.room_count)
		return (NULL);
	room = g_lem.rooms;
	while (index-- && room->next)
		room = room->next;
	return (room);
}

int				free_ret(char *line, int ret)
{
	free(line);
	return (ret);
}

