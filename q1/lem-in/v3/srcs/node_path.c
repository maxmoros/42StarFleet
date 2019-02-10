#include "lem_in.h"

t_path		*new_path(void)
{
	int		i;
	int		room;
	int		step;
	t_path	*path;

	if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
		exit_lem("Malloc failed 3\n");
	path->length = g_lem.occupied[g_lem.room_count - 1];
	if (!(path->trail = (char**)ft_memalloc(sizeof(char*) * path->length + 1)))
		exit_lem("Malloc failed 2\n");
	path->trail[path->length] = NULL;
	room = g_lem.room_count - 1;
	step = path->length - 1;
	path->trail[step] = get_room(room)->name;
	while (room)
	{
		i = -1;
		while (++i < g_lem.room_count)
			if (g_lem.map[room][i] > 0 && g_lem.occupied[i] == step)
			{
				path->trail[--step] = get_room(i)->name;
				room = i;
				break;
			}
	}
	return (path);
}

int			qmax_flow(void)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < g_lem.room_count)
		if (g_lem.map[0][i] > 0)
			count++;
	return (count);
}

int				num_paths_touse(int path_count)
{
	int		w;
	int		s;

	w = 0;
	s = 0;
	while (s < g_lem.ants && ++w < path_count)
		s += (g_lem.x[w] - g_lem.x[w - 1]) * w;
	if (!(g_lem.y = (int*)ft_memalloc(sizeof(int) * w)))
		return (0);
	if (!(g_lem.paths = (t_path**)ft_memalloc(sizeof(t_path*) * (w + 1))))
		return (0);
	g_lem.paths[w] = NULL;
	return (w);
}

void			ants_per_path(void)
{
	int		n;
	int		i;

	n = g_lem.ants;
	while (n--)
	{
		i = g_lem.w - 1;
		while (i > 0 &&
				(g_lem.x[i] + g_lem.y[i]) >= (g_lem.x[i - 1] + g_lem.y[i - 1]))
			i--;
		ft_putnbr(i);//##########
		ft_putstr(", ");//#######
		g_lem.y[i]++;
	}
	ft_putstr("\n");
}

void		get_paths(void)
{
	int		i;

	g_lem.qmax = qmax_flow();
	if (!(g_lem.paths = (t_path**)ft_memalloc(sizeof(t_path*) * (g_lem.qmax + 1))))
		exit_lem("Malloc failed 1\n");
	if (!(g_lem.x = (int*)ft_memalloc(sizeof(int) * (g_lem.qmax))))
		exit_lem("Malloc failed 0\n");
	i = -1;
	clear_occupied(0);
	while (++i < g_lem.qmax)
	{
		ft_putstr("\nPATH:\n");
		g_lem.occupied[0] = 1;
		bfs_map();
		if (!has_solution())
			break;
		g_lem.x[i] = g_lem.occupied[g_lem.room_count - 1];
		ft_putstr("Length = ");
		ft_putnbr(g_lem.x[i]);
		ft_putstr("\n");
		g_lem.paths[i] = new_path();
		print_path(g_lem.room_count - 1, 0, 1);
		clear_occupied(1);
	}
	g_lem.w = num_paths_touse(i);
	ants_per_path();
}
