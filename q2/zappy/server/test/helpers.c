#include "server.h"
#include "test.h"
#include "tile_type.h"
#include "player_type.h"
#include "g_player_list.h"

int				place_stone(int type, t_tile *t)
{
	assert(t);
	t->count[type] += 1;
	return (0);
}

char **stone_names = (char *[]){ "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", NULL };

char system_sprintf_buf[4096] = { 0 };
int place_food(t_tile *t);

t_player		*new_player_on_tile(int team_id, int x, int y)
{
	t_player	*p;

	p = new_player(team_id);
	add_player_to_tile(p, &g_map->tile[x][y]);
	return (p);
}

t_player	*is_player_on_tile(t_player *p, t_tile *t)
{
	int			i;

	i = -1;
	while (++i < t->parray_size)
		if (t->players[i] == p)
			break ;
	if (i == t->parray_size)
		return (0);
	else
		return (p);
}

void init_user_commands_test_gamestate(void)
{
	int mapx = 18;
	int mapy = 18;
	game_init(mapx, mapy, 1, 0);
	t_player *p1 = new_player_on_tile(0, 1, 0);
	t_player *p2 = new_player_on_tile(0, 2, 0);
	p1->facing = SOUTH;
	p2->facing = WEST;
	g_map->tile[0][0].count[FOOD] += 1;
	g_map->tile[3][0].count[FOOD] += 1;
	g_map->tile[3][0].count[FOOD] += 1;
	g_map->tile[2][1].count[FOOD] += 1;
	place_stone(0, &g_map->tile[0][0]);
	place_stone(1, &g_map->tile[1][0]);
	place_stone(5, &g_map->tile[3][0]);
	place_stone(2, &g_map->tile[0][1]);
	place_stone(3, &g_map->tile[0][1]);
	place_stone(0, &g_map->tile[1][1]);
	place_stone(4, &g_map->tile[1][1]);
	p2->count[MENDIANE] = 2;

	/* map will look like:
	 * [food,   stone0] [player1(south), stone1] [player2(west, inventory: stone3(x2))] [food, food, stone5]
	 * [stone2, stone3] [stone0, stone4        ] [food                                ] [                  ] */
}

void fill_test_g_opts(void)
{
	g_opts.server_port = 0x0;
	g_opts.world_width = 23;
	g_opts.world_height = 19;
	g_opts.teamcount = 3;
	g_opts.team_names = calloc(4, sizeof(char *));
	g_opts.team_names[1] = "zerg";
	g_opts.team_names[0] = "protoss";
	g_opts.team_names[2] = "terran";
	g_opts.initial_players_per_team = 2;
}

void start_game_with_fake_options(void)
{
	fill_test_g_opts();
	game_init(g_opts.world_width, g_opts.world_height,
			g_opts.teamcount, g_opts.initial_players_per_team);

}

void test_server_listen(void)
{
	start_game_with_fake_options();
	socket_lookup_init(1);
	listen_for_connections(g_opts.server_port);
}

int	get_port_from_fd(int fd)
{
	struct sockaddr_in addr;
	socklen_t len;

	len = sizeof(addr);
	getsockname(fd, (struct sockaddr *)&addr, &len);
	return (ntohs(addr.sin_port));
}

int get_server_port(void)
{
	return (get_port_from_fd(get_server_fd()));
}

int string_equal_file_contents(char *expect_string, char *filepath)
{
	size_t bufsize = strlen(expect_string) + 1;
	char *actual = malloc(bufsize);
	bzero(actual, bufsize);
	int fd = open(filepath, O_RDONLY | O_CREAT);
	read(fd, actual, bufsize - 1);
	int success = !strcmp(actual, expect_string);
	free(actual);
	close(fd);
	return success;
}
void           print_map_info(void)
{
	t_tile      *t;
	int         x, y;

	x = -1;
	y = -1;
	while (++x < g_map->dim.x)
	{
		while (++y < g_map->dim.y)
		{
			t = &g_map->tile[x][y];
			printf("(%d, %d)", t->x, t->y);
			printf(" \tStones: [  %d,  %d,  %d,  %d,  %d,  %d ]", t->count[LINEMATE], t->count[DERAUMERE], t->count[SIBUR], t->count[MENDIANE], t->count[PHIRAS], t->count[THYSTAME]);
			printf(" Food: [ %d ] Players: %d", t->count[FOOD], t->count[PLAYERS]);
			printf("\n");
		}
		y = -1;
	}
}

int		lowest_active_player_id(void)
{
	int i = 1;
	while (1)
	{
		if (g_player_list[i])
		{
			return i;
		}
		++i;
	}
}
