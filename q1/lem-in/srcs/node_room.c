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
							//`		ft_putstr("\t\taa\n");
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

int		count_rooms(void)
{
	t_room	*node;

	node = g_lem.rooms;
	g_lem.room_count = 1;
	while ((node = node->next))
		g_lem.room_count++;
	node = g_lem.rooms;
	while (node)
	{
		if (!(node->adjc = (char*)ft_memalloc(g_lem.room_count + 1)))
			return (0);	
		node = node->next;
	}
	if (!(g_lem.occupied = (char*)ft_memalloc(g_lem.room_count + 1)))
		return (0);
	return (1);
}

void	print_rooms(void)
{
	t_room	*node;
	int		i;

	node = g_lem.rooms;
	ft_putstr("\n\tROOM NETWORK\n");
	while (node)
	{
		ft_putstr(node->name);
		ft_putstr("\t: ");
		i = -1;
		while (++i < g_lem.room_count)
			if (node->adjc[i])
				ft_putchar('1');
			else
				ft_putchar('0');
		ft_putstr("\n");
		node = node->next;
	}
	ft_putstr("\n");
}