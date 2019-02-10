#include "server.h"
#include "test.h"

void test_parses_error_free_command_line_options(void)
{
	char *tn[] = { "zerg", "protoss", "terran", NULL };
	struct s_opts correct_opts = {
		.server_port = 4321,
		.world_width = 90,
		.world_height = 20,
		.initial_players_per_team = 3,
		.tickrate = 100,
		.team_names = tn,
	};
	char *argv[] = {"./test_server", "-p", "4321", "-x", "90", "-y", "20", "-c", "3", "-t", "100", "-n", "zerg", "protoss", "terran", NULL };
	int argc = 15;
	parse_options(argc, argv);
	assert(correct_opts.server_port == g_opts.server_port);
	assert(correct_opts.world_width == g_opts.world_width);
	assert(correct_opts.world_height == g_opts.world_height);
	assert(correct_opts.initial_players_per_team == g_opts.initial_players_per_team);
	assert(correct_opts.tickrate == g_opts.tickrate);
	int i;
	for (i = 0; tn[i]; i++)
		assert(!strcmp(correct_opts.team_names[i], g_opts.team_names[i]));
	assert(g_opts.team_names[i] == NULL);
}

void test_parse_options(void)
{
	test_parses_error_free_command_line_options();
	printf("%s: ok\n", __FILE__);
	// also test error ones
}
