#include "lem_in.h"

t_room	*new_room(char *name, int x, int y, t_room *next)
{
	t_room	*node;

	if (!(node = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	node->name = ft_strdup(name);
	node->next = next;
	node->tube = NULL;
	node->x = x;
	node->y = y;
	node->prev = NULL;
	return (node);
}

t_room	*line_room(char *line, t_room *next)
{
	char	**parts;
	int		i;
	t_room	*node;

	parts = ft_strsplit(line, ' ');
	i = 0;
	while (parts[i])
		i++;
	node = NULL;
	if (i == 3 && ft_isint(parts[1]) && ft_isint(parts[2]))
		node = new_room(parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]), next);
	while (i-- > 0)
		free(parts[i]);
	free(parts);
	return (node);
}

int		ht_line(char *line)
{
	t_room	*node;

	if (!ft_strcmp(line, "##start"))
	{
		if ((g_lem.check & 0x01)
				|| !(g_lem.check |= 0x01)
				|| get_next_line(1, &line) != 1
				|| !(g_lem.rooms = line_room(line, g_lem.rooms)))
			return (0);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		node = g_lem.rooms;
		while (node && node->next)
			node = node->next;
		if ((g_lem.check & 0x02) || !(g_lem.check |= 0x02)
				|| get_next_line(1 ,&line) != 1)
			return (0);
		if ((node && !(node->next = line_room(line, NULL)))
				|| !(g_lem.rooms = line_room(line, NULL)))
			return (0);
	}
	return (1);
}

int		data_line(char *line)
{
	return (ft_atoi(line));
}

int		build_map(void)
{
	char	*line;

	while (get_next_line(1, &line) == 1)
	{
		if (!(line[0] == '#' ? ht_line(line) : data_line(line)))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (g_lem.check == 0x03 ? 1 : 0);
}
