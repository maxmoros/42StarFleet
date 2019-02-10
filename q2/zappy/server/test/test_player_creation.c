#include "server.h"
#include "tile_type.h"
#include "test.h"

int			test_player_creation(void)
{
	t_player	*p;
	t_tile		*t;

	create_map(10, 10);
	t = &g_map->tile[0][0];
	for(int i = 0; i < 4000; i++)
	{
		p = new_player(1);
		add_player_to_tile(p, t);
	}
	assert(is_player_on_tile(p, t) == p);
	printf("%s: ok\n", __FILE__);
	return (0);
}
