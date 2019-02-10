#include "server.h"
#include "player_type.h"
#include "tile_type.h"

int			test_player_movement(void)
{
	t_player		*p;

	create_map(13, 17);

	t_tile *t = &g_map->tile[5][5];
	p = new_player(1);
	add_player_to_tile(p, t);

	for (int i = 0; i < 34817; i++) //ends at t->x, t->y - 1
		move_player(p, NORTH);
	assert(p->tile->x == t->x && p->tile->y == t->y - 1);
	for (int i = 0; i < 26625; i++) //ends at t->x + 1, t->y - 1
		move_player(p, EAST);
	assert(p->tile->x == t->x + 1 && p->tile->y == t->y - 1);
	for (int i = 0; i < 34817; i++) //ends at t->x + 1, t->y
		move_player(p, SOUTH);
	assert(p->tile->x == t->x + 1 && p->tile->y == t->y);
	for (int i = 0; i < 26625; i++) //ends at t->x, t->y
		move_player(p, WEST);
	assert(p->tile->x == t->x && p->tile->y == t->y);

	move_player(p, NORTH);
	move_player(p, NORTH);
	move_player(p, NORTH);
	move_player(p, NORTH);
	move_player(p, NORTH);
	move_player(p, WEST);
	move_player(p, WEST);
	move_player(p, WEST);
	move_player(p, WEST);
	move_player(p, WEST);
	assert(p->tile->x == t->x - 5 && p->tile->y == t->y - 5);
	printf("%s: ok\n", __FILE__);
	return (0);
}
