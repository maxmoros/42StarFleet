#include "server.h"
#include "tile_type.h"

int	test_map_creation(void)
{
	int			pool;

	create_map(10, 10);
	for (int x = 0; x < g_map->dim.x; x++)
		for (int y = 0; y < g_map->dim.y; y++)
			assert(g_map->tile[x][y].x == x && g_map->tile[x][y].y == y);

	printf("%s: ok\n", __FILE__);
	return (0);
}
