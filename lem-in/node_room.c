#include "lem_in.h"

t_room	*new_room(char *name, int x, int y, t_room *next)
{
	t_room	*node;

	if (!(node = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	node->name = ft_strdup(name);
	node->next = next;
	node->adjc = NULL;
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
							//		ft_putstr("\t\taa\n");
	i = 0;
	while (parts[i])
		i++;
							//		ft_putstr("\t\tbb\n");
	node = NULL;
	if (i == 3 && ft_isint(parts[1]) && ft_isint(parts[2]))
	{
		node = new_room(parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]), next);
		printf("%s room at (%d, %d)\n", parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]));
	}
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
				|| (!node && !(g_lem.rooms = line_room(line, NULL))))
			return (0);
	}
	return (1);
}

int		valid_name(char *name)
{
	t_room	*node;

	node = g_lem.rooms;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
			return (1);
		node = node->next;
	}
	return (0);
}

int		name_index(char *name)
{
	t_room	*node;
	int		count;

	node = g_lem.rooms;
	count = 0;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
			return (count);
		count++;
		node = node->next;
	}
	return (-1);
}

int		line_path(char *line)
{
	char	**parts;
	int		i;
	int		ret;

	ret = 1;
	parts = ft_strsplit(line, '-');
	i = 0;
	while (parts[i])
		i++;
	if (i != 2 || !valid_name(parts[0]) || !valid_name(parts[1]))
		ret = 0;
	else if (g_lem.check & PATH)
	{
		printf("link from %s to %s\n", parts[0], parts[1]);
	}
	while (i-- > 0)
		free(parts[i]);
	free(parts);
	return (ret);
}

int		data_line(char *line)
{
								//	ft_putstr("\ta\n");
	if (!(g_lem.check & PATH) && !line_path(line))
	{
								//	ft_putstr("\tc\n");
		if (g_lem.check & START)
		{
								//	ft_putstr("\te\n");
			if (!(g_lem.rooms->next = line_room(line, g_lem.rooms->next)))
				return (0);
		}
		else if (!(g_lem.rooms = line_room(line, g_lem.rooms)))
			return (0);
	}
	else if (!(g_lem.check & PATH))
	{
								//	ft_putstr("\tb\n");
		g_lem.check |= PATH;
		line_path(line);
	}
	else if (!line_path(line))
		return (0);
								//	ft_putstr("\td\n");
	return (1);
}

int		build_map(void)
{
	char	*line;

	while (get_next_line(1, &line) == 1 && line[0])
	{
		if (!(line[0] == '#' ? ht_line(line) : data_line(line)))
		{
			printf("Invalid line : \"%s\"\n", line);
			free(line);
			return (0);
		}
		free(line);
	}
	return (g_lem.check == 0x07 ? 1 : 0);
}
