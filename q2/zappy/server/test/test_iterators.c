#include "test.h"
#include "server.h"
#include "clients_lookup.h"

void		test_iter_tiles(void)
{
	t_tile	**copy;
	t_tile	*t;
	int		i;
	int		j;

	game_init(5, 9, 1, 1);
	copy = calloc(g_map->dim.x * g_map->dim.y + 1, sizeof(t_tile *));
	i = 0;
	while ((copy[i] = iter_tiles()))
		i++;
	for (i = 0; i < g_map->dim.x; i++)
		for (j = 0; j < g_map->dim.y; j++)
			assert(*copy++ = &g_map->tile[i][j]);
}

static int kill_these_first[2] = { 3, 6 };
static int then_kill_this_one = 2;

void		set_up_game_with_nine_initial_players_of_whom_two_are_dead(void)
{
	int	*dead_pids;
	int num_killed;

	game_init(1, 1, 1, 9);
	mark_player_for_death(get_player(kill_these_first[0]));
	mark_player_for_death(get_player(kill_these_first[1]));
	dead_pids = kill_and_return_dead_players(&num_killed);
	assert(num_killed == 2);
	assert((dead_pids[0] == kill_these_first[0] && dead_pids[1] == kill_these_first[1])
			|| (dead_pids[1] == kill_these_first[0] && dead_pids[0] == kill_these_first[1]));
	assert(g_map->players == 7);
}

void		kill_off_another_player(void)
{
	mark_player_for_death(get_player(then_kill_this_one));
	kill_and_return_dead_players((int[]){});
	assert(g_map->players == 6);
}

int			player_array_contains_id(t_player **ary, int pid)
{
	for (int i = 0; ary[i]; i++)
		if (ary[i]->id == pid)
			return (1);
	return (0);
}

void		test_iter_players(void)
{
	t_player	**copy;
	int			i;

	set_up_game_with_nine_initial_players_of_whom_two_are_dead();
	copy = calloc(8, sizeof(t_player *));
	i = 0;
	while ((copy[i] = iter_players()))
		i++;
	assert(i == 7);
	assert(!player_array_contains_id(copy, kill_these_first[0]));
	assert(!player_array_contains_id(copy, kill_these_first[1]));
	int player_was_in_copy;
	i = 0;
	for (int players_checked = 0; players_checked < 7; i++)
	{
		if (get_player(i))
		{
			assert(player_array_contains_id(copy, get_player(i)->id));
			players_checked++;
		}
	}
	kill_off_another_player();
	copy = calloc(7, sizeof(t_player *));
	i = 0;
	while ((copy[i] = iter_players()))
		i++;
	i = 0;
	for (int players_checked = 0; players_checked < 6; i++)
	{
		if (get_player(i))
		{
			assert(player_array_contains_id(copy, get_player(i)->id));
			players_checked++;
		}
	}
	assert(!player_array_contains_id(copy, then_kill_this_one));
}

int		clients_array_count(t_client **ary, t_client *c)
{
	int count = 0;
	while (*ary)
	{
		if (c == *ary)
			count++;
		ary++;
	}
	return (count);
}

void		test_iter_clients(void)
{
	t_client	**gfx_copy;
	t_client	**players_copy;
	t_client	**all_copy;
	int			nclients;
	int			found;

	bzero(g_clients, sizeof(g_clients));
	g_count_clients = 0;
	nclients = 20;
	for (int i = 0; i < nclients; i++)
	{
		if (i % 2 == 0)
			register_client(i, i, GFX);
		else
			register_client(i, i, ACTIVE_PLAYER);
	}
	gfx_copy = calloc(nclients + 1, sizeof(t_client *));
	players_copy = calloc(nclients + 1, sizeof(t_client *));
	all_copy = calloc(nclients + 1, sizeof(t_client *));
	for (int i = 0; (players_copy[i] = iter_clients(ACTIVE_PLAYER)); i++)
		;
	for (int i = 0; (gfx_copy[i] = iter_clients(GFX)); i++)
		;
	for (int i = 0; (all_copy[i] = iter_clients(-1)); i++)
		;
	for (t_client **clients = g_clients; clients[0]; clients++)
	{
		t_client **expect_one = clients[0]->type == GFX ? gfx_copy : players_copy;
		t_client **expect_none = clients[0]->type == GFX ? players_copy : gfx_copy;
		assert(clients_array_count(expect_one, clients[0]) == 1);
		assert(clients_array_count(expect_none, clients[0]) == 0);
		assert(clients_array_count(all_copy, clients[0]) == 1);
	}
}

void		test_iterators(void)
{
	test_iter_tiles();
	test_iter_players();
	test_iter_clients();
	printf("%s: ok\n", __FILE__);
}
