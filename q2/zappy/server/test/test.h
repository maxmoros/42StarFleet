#ifndef TESTING
# define TESTING
# include <fcntl.h>
# include <sys/resource.h>
# include "tile_type.h"
# include "command_list_type.h"
# include "command_type.h"
# include "client_type.h"
# include "player_type.h"
extern int g_make_server_die;
extern int g_server_fd;
extern char system_sprintf_buf[4096];
extern char **stone_names;

#define fork_and_call_system(format, ...)\
	if (!fork()) {\
		sprintf(system_sprintf_buf, format, __VA_ARGS__);\
		system(system_sprintf_buf);\
		exit(0);\
	}

// helpers.c
int	place_food(t_tile *t);
int	get_port_from_fd(int fd);
int get_server_port(void);
void test_server_listen(void);
void quicksleep(void);
int string_equal_file_contents(char *expect_string, char *filepath);
void start_game_with_fake_options(void);
void init_user_commands_test_gamestate(void);
int lowest_active_player_id(void);
int	place_stone(int type, t_tile *t);
t_player	*is_player_on_tile(t_player *p, t_tile *t);
t_player		*new_player_on_tile(int team_id, int x, int y);

// tests_see.c
void	fill_col_resources(int x, int y1, int y2, int quantity, int type);
void	fill_col_resources(int y, int x1, int x2, int quantity, int type);
void	place_resource(int type, int y, int x);

#endif
