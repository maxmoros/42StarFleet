#include "server.h"
#include "tile_type.h"
#include "test.h"

/* Optionally print the results of movements */
//#define PRINTF_MOVES

static void		go(int dir, t_tile **t_ptr, int amt)
{
	for (int i = 0; i < amt; i++)
		*t_ptr = get_adj_tile(*t_ptr, dir);
#ifdef PRINTF_MOVES
	printf("Moved %d in dir %d -- Curr tile: (%d, %d)\n", amt, dir, (*t_ptr)->x, (*t_ptr)->y);
#endif
}

int			test_map_movement(void)
{
	t_tile		*t;

	start_game_with_fake_options();
	create_map(17, 7);
	t = &g_map->tile[0][0];
	go(NORTH, &t, 137);
	go(WEST, &t, 93);
	go(SOUTH, &t, 57);
	go(EAST, &t, 127);
	go(SOUTHEAST, &t, 293);
	go(NORTHEAST, &t, 73);
	go(SOUTHWEST, &t, 999);
	go(NORTHWEST, &t, 420);
	assert(t->x == 1 && t->y == 5);
	printf("%s: ok\n", __FILE__);
	return (0);
}
