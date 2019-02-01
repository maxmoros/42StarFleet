#include "lem_in.h"

t_lem	g_lem;

void    init_lem()
{
    g_lem.rooms = NULL;
    g_lem.paths = NULL;
    g_lem.ants = 0;
    g_lem.check = 0;
}

int     get_ants()
{
    char    *line;

    printf("Getting ants\n");
    if (get_next_line(0, &line) < 1)
        return (0);
    while (line[0] == '#' && line[1] != '#')
        if (get_next_line(1, &line) < 1)
            return (0);
    if (!ft_isint(line) || !ft_isalldig(line))
        return (0);
    g_lem.ants = ft_atoi(line);
    printf("Number of ants = %d\n", g_lem.ants);
    return (g_lem.ants > 0 ? 1 : 0);
}

int		build_logic_map(void)
{
	char	**map;
	t_room	*room;
	int		i;

	if (!(map = (char**)ft_memalloc(sizeof(char) * g_lem.room_count)))
		return (0);
	i = -1;
	room = g_lem.rooms;
	while (room && ++i < g_lem.room_count)
	{
		if (!(map[i] = (char*)ft_memalloc(sizeof(char) * g_lem.room_count)))
			return (0);
		ft_strcpy(map[i], room->adjc);
		room = room->next;
	}
	g_lem.map = map;
	return (1);
}

int		traverse_map(void)
{
	return (0);	
}
