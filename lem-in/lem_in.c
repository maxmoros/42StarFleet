#include "lem_in.h"

void	lem_in(void)
{
	if (!get_ants() || !build_map())
	{
		ft_putstr("ERROR\n");
		exit(1);
	}
	print_rooms();
}

int		main(void)
{
	lem_in();
	return (0);
}
