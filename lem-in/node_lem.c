#include "len-in.h"

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

    if (get_next_line(1, &line) < 1)
        return (0);
    while (line[0] == '#' && line[1] != '#')
        if (get_next_line(1, &line) < 1)
            return (0);
    if (!ft_isint(line) || !ft_isalldig(line))
        return (0);
    g_lem.ants = ft_atoi(line);
    return (1);
}