#include <lem_in.h>

void	build_logic_map(void)
{
	t_room	*room;
	int		i;

	if (!(g_lem.map = ft_memalloc(sizeof(char*) * (g_lem.room_count + 1))))
		exit_lem("Malloc error 4\n");
	g_lem.map[g_lem.room_count] = NULL;
	if (!(g_lem.occupied = (int*)ft_memalloc(sizeof(int) * g_lem.room_count)))
		exit_lem("Malloc error 5\n");
	i = -1;
	room = g_lem.rooms;
	while (++i < g_lem.room_count)
	{
		g_lem.map[i] = room->adjc;
		room = room->next;
	}
}

int		has_solution(void)
{
	if (g_lem.occupied[g_lem.room_count - 1] > 0)
		return (1);
	return (0);
}

void	bfs_map(void)
{
	int		i;
	int		j;
	int		k;
	char	updoot;

	i = 0;
	updoot = 1;
	while (updoot-- == 1 && g_lem.occupied[g_lem.room_count - 1] == 0)
	{
		i++;
		j = -1;
		while (++j < g_lem.room_count)
			if (g_lem.occupied[j] == i && (k = -1))
				while (++k < g_lem.room_count)
					if (g_lem.map[j][k] == 1 && !g_lem.occupied[k])
					{
						g_lem.occupied[k] = i + 1;
						updoot = 1;
					}

	}
}

void			print_path(int room_number, int start, int block)
{
	int		i;
	int		step;

	if (room_number == start)
	{
		ft_putstr(get_room(room_number)->name);
		ft_putstr("->");
		return ;
	}
	step = g_lem.occupied[room_number];
	i = -1;
	while (++i < g_lem.room_count)
		if (g_lem.map[room_number][i] == 1 && g_lem.occupied[i] == step - 1)
		{
			print_path(i, start, block);
			ft_putstr(get_room(room_number)->name);
			if (block && room_number != g_lem.room_count - 1)
				g_lem.occupied[room_number] = -1;
			if (room_number != g_lem.room_count - 1)
				ft_putstr("->");
			else
				ft_putstr("\n");
			break;
		}
}

void	clear_occupied(int block)
{
	int		i;

	if (block)
	{
		i = -1;
		while (++i < g_lem.room_count)
			if (g_lem.occupied[i] > 0)
				g_lem.occupied[i] = 0;
	}
	else
		ft_bzero(g_lem.occupied, sizeof(int) * g_lem.room_count);
}
