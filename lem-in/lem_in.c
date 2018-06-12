#include "lem_in.h"

t_lem	g_lem;

void	lem_in(void)
{
	get_ants();
	build_map();
}

int		main(void)
{
	lem_in();
	return (0);
}
