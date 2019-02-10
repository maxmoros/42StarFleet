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

void			print_occupied(void)
{
	int		i;

	i = -1;
	ft_putstr("Occupied\n[");
	while (++i < g_lem.room_count)
	{
		ft_putnbr(g_lem.occupied[i]);
		if (i < g_lem.room_count - 1)
			ft_putstr(", ");
	}
	ft_putstr("]\n");
}
