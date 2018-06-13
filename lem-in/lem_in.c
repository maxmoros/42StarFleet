#include "lem_in.h"

void	lem_in(void)
{
	ft_putstr("A\n");
	if (!get_ants())
		return ;
	ft_putstr("B\n");
	if (!build_map())
		return ;
	ft_putstr("C\n");
	print_rooms();
}

int		main(void)
{
	lem_in();
	return (0);
}
