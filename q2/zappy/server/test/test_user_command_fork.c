#include "server.h"
#include "test.h"

void	test_one_player_can_fork_once(void)
{
	game_init(1, 1, 1, 0);
	t_player *p = new_player_on_tile(0, 0, 0);
	fork_player(p->id, NULL);
	for (int ticks = 0; ticks < 600; ticks++)
		check_and_hatch_eggs();
	assert(p->tile->count[PLAYERS] == 1);
	check_and_hatch_eggs();
	assert(p->tile->count[PLAYERS] == 2);
}

void	test_many_forks(void)
{
	game_init(1, 1, 1, 0);
	t_player *p = new_player_on_tile(0, 0, 0);
	for (int ticks = 0; ticks < 630; ticks++)
	{
		if (ticks < 20)
			fork_player(p->id, NULL);
		check_and_hatch_eggs();
	}
	assert(p->tile->count[PLAYERS] == 21);
}

void	test_user_command_fork(void)
{
	test_one_player_can_fork_once();
	test_many_forks();
	printf("%s: ok\n", __func__);
}
