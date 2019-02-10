#include "incantation.h"
#include "test.h"
#include "g_player_list.h"

struct	s_incant_args *get_eventual_incantation_result(t_player *p);
// copied from a now-deleted file because this test is weirdly reliant on it
int			*get_current_tile_player_count(int pid, int *count)
{
	t_player		*p;
	t_tile			*t;
	int				i;
	int				j;
	int				*res;

	p = get_player(pid);
	t = p->tile;
	*count = t->count[PLAYERS];
	if ((res = malloc(sizeof(int *) * t->count[PLAYERS])) == NULL)
		ERR_OUT("get_current_tile_player_count; malloc");
	i = -1;
	j = -1;
	while (++i < t->count[PLAYERS])
	{
		assert(t->players[i] != NULL);
		res[++j] = t->players[i]->id;
	}
	return (res);
}

void	do_incant_args_creation_test(int *levels, t_objcount ct, int should_succeed)
{
	int num_players = ct[PLAYERS];
	game_init(1, 1, 1, num_players);
	for (int i = 0; i < num_players; i++)
		assign_avatar(0);
	int _nothing;
	int *pids = get_current_tile_player_count(lowest_active_player_id(),
			&_nothing);
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		get_player(pids[i])->level = levels[i];
	}
	memcpy(g_map->tile[0][0].count, ct, sizeof(t_objcount));
	int priest_id = pids[0];
	struct s_incant_args *result = get_eventual_incantation_result(get_player(priest_id));
	if (should_succeed)
	{
		assert(get_player(priest_id));
		assert(result->new_level == get_player(priest_id)->level + 1);
		if (levels[0] > 1)
			assert(result->group_size > 1);
		assert(0 != memcmp(ct, g_map->tile[0][0].count, sizeof(t_objcount)));
	}
	else
	{
		assert(get_player(priest_id));
		assert(result->new_level == get_player(priest_id)->level);
		assert(result->group_size == 1);
		assert(0 == memcmp(ct, g_map->tile[0][0].count, sizeof(t_objcount)));
	}
}

void	test_creates_correct_incant_args(void)
{
	int playerlevels[] = {
		-1, // put real guy here
		1,
		2, 2,
		3, 3,
		4, 4, 4, 4,
		5, 5, 5, 5,
		6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7,
		8
	};
	t_objcount ct = { [LINEMATE] = 99, [MENDIANE] = 99, [THYSTAME] = 99,
		[DERAUMERE] = 99, [SIBUR] = 99, [PHIRAS] = 99, [PLAYERS] = 0 , [FOOD] = 0};
	ct[PLAYERS] = sizeof(playerlevels) / sizeof(*(playerlevels));

	// pass because there's tons of everything:
	for (int i = 1; i < 8; i++)
	{
		playerlevels[0] = i;
		do_incant_args_creation_test(playerlevels, ct, 1);
	}
	// fail because not enough players at correct level:
	ct[PLAYERS] = 1;
	do_incant_args_creation_test((int []){ 2 }, ct, 0);
	do_incant_args_creation_test((int []){ 3 }, ct, 0);
	ct[PLAYERS] = 3;
	do_incant_args_creation_test((int []){ 4, 4, 4 }, ct, 0);
	do_incant_args_creation_test((int []){ 5, 5, 5 }, ct, 0);
	ct[PLAYERS] = 5;
	do_incant_args_creation_test((int []){ 6, 6, 6, 6, 6 }, ct, 0);
	do_incant_args_creation_test((int []){ 7, 7, 7, 7, 7 }, ct, 0);
	//fail because can't level past 8:
	ct[PLAYERS] = 10;
	do_incant_args_creation_test((int []){ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, ct, 0);

	// fail because not enough stones:
	ct[LINEMATE] = 0;
	ct[PLAYERS] = (sizeof(playerlevels) / sizeof(*(playerlevels)));
	for (int i = 1; i < 8; i++)
	{
		playerlevels[0] = i;
		do_incant_args_creation_test(playerlevels, ct, 0);
	}
}

void	test_incantation_start_to_finish(int should_succeed)
{
	struct s_incant_args *a;
	int num_players = 8;
	int priest_level = 4;
	int new_level = priest_level + !!should_succeed;

	game_init(1, 1, 1, num_players);
	for (int i = 0; i < num_players; i++)
		assign_avatar(0);
	int _nothing;
	int *pids = get_current_tile_player_count(lowest_active_player_id(),
			&_nothing);
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		if (i % 2 == 0)
			get_player(pids[i])->level = priest_level;
		else
			get_player(pids[i])->level = 1;
	}
	t_objcount ct = { [LINEMATE] = 1, [DERAUMERE] = 1, [SIBUR] = 2,
		[MENDIANE] = 0, [PHIRAS] = 1, [THYSTAME] = 0, [PLAYERS] = num_players };
	if (should_succeed == 0)
		ct[SIBUR] -= 1;
	memcpy(g_map->tile[0][0].count, ct, sizeof(ct));
	a = get_eventual_incantation_result(get_player(pids[0]));
	char *response = incantation_finish(pids[0], a);
	char *expected;
	asprintf(&expected, "current level %d\n", new_level);
	assert(!strcmp(response, expected));
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		if (i % 2 == 0)
			assert(get_player(pids[i])->level == new_level);
		else
			assert(get_player(pids[i])->level == 1);
	}
}

void	test_user_command_incantation(void)
{
	test_creates_correct_incant_args();
	test_incantation_start_to_finish(1);
	test_incantation_start_to_finish(0);
	printf("%s: ok\n", __FILE__);
}
