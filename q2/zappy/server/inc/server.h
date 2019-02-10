/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:25 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:25 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <arpa/inet.h>
# include <assert.h>
# include <limits.h>
# include <netdb.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/signal.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <unistd.h>
# include "language_defs.h"

# define MAX_COMMANDS		10
# define ERR_OUT(msg)		({ perror(msg); exit(-1); })

enum							e_object_type
{
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD,
	PLAYERS,
	NUM_ENUMERATED_OBJECTS
};

typedef int						t_objcount[NUM_ENUMERATED_OBJECTS];

# define MIN_STONE LINEMATE
# define MAX_STONE THYSTAME
# define MAX_OBJ_NAME_LENGTH 10

# define MAX_CLIENTS (FD_SETSIZE - 4)

# define FATAL(msg) ({ fprintf(stderr, "%s: %s\n", __func__, msg); exit(-1); })

# define MAX_TEAM_NAME_LENGTH 63
# define MAX_BROADCAST_LENGTH 4096

# define ENERGY_PER_FOOD 126

typedef char					*(*t_cmdfunc)(int player_id, void *args);
typedef struct s_command		t_command;
typedef struct s_command_list	t_command_list;
typedef struct s_command_queue	t_command_queue;
typedef struct s_ply_cmd_queue	t_ply_cmd_queue;
typedef struct s_client			t_client;
typedef struct					s_vec
{
	int x;
	int y;
}								t_vec;
typedef struct s_tile			t_tile;
typedef struct s_player			t_player;

enum							e_socktype
{
	HANDSHAKE,
	SERVER,
	ACTIVE_PLAYER,
	GFX
};

enum							e_directions
{
	NORTH = 1,
	NORTHWEST = 2,
	WEST = 3,
	SOUTHWEST = 4,
	SOUTH = 5,
	SOUTHEAST = 6,
	EAST = 7,
	NORTHEAST = 8
};

typedef struct					s_plist
{
	t_player			*p;
	struct s_plist		*next;
}								t_plist;

typedef struct					s_game_info
{
	t_tile				**tile;
	t_vec				dim;
	int					teams;
	int					players;
	int					*players_on_team;
	t_plist				**empty_avatars;
}								t_game_info;

t_game_info						*g_map;
extern struct					s_opts
{
	int					tickrate;
	int					server_port;
	int					world_width;
	int					world_height;
	int					initial_players_per_team;
	char				**team_names;
	int					teamcount;
}								g_opts;

/*
** game/player_data_api.c
*/

int								add_player_to_list(t_player *t);
void							player_list_init(void);
t_player						*get_player(int pid);
int								get_player_list_size(void);

int								delete_player_from_list(t_player *p);
void							cleanup_player_list(void);

int								move_player(t_player *p, int dir);

int								create_map(int x, int y);

enum e_object_type				get_object_type(char *object_name);

int								game_init(int x, int y, int teams, int players);
t_tile							*get_random_tile(void);

void							game_upkeep(void);

int								assign_avatar(int team_id);
t_player						*new_player(int team_id);
void							reset_pid(void);

int								mark_player_for_death(t_player *p);
int								*kill_and_return_dead_players(int *size);

void							increase_player_level(t_player *p, int new_lvl);
int								get_winning_teams(int **team_ids_ptr);

int								get_team_open_slots(int team);
int								get_team_open_slots_by_pid(int pid);
int								add_player_to_team_waitlist(t_player *p);
t_player						*remove_player_from_waitlist(int team);

t_tile							*get_adj_tile(t_tile *home, int dir);

int								remove_player_from_tile(t_player *p, t_tile *t);
int								add_player_to_tile(t_player *p, t_tile *t);

void							do_per_tick_resource_generation(void);
void							seed_tiles_initial_resources(void);

t_tile							*iter_tiles(void);
t_player						*iter_players(void);
t_client						*iter_clients(int type);

/*
** User commands:
*/

char							*advance(int player_id, void *arg);
char							*left(int player_id, void *args);
char							*right(int player_id, void *args);
char							*see(int player_id, void *arg);
char							*inventory(int player_id, void *arg);
char							*take(int player_id, void *arg);
char							*put(int player_id, void *arg);
char							*kick(int player_id, void *arg);
char							*broadcast(int player_id, void *arg);
char							*incantation(int player_id, void *arg);
char							*incantation_finish(int player_id, void *arg);
char							*fork_player(int player_id, void *arg);
char							*fork_finish(int player_id, void *arg);
char							*connect_nbr(int player_id, void *arg);

char							*ok_response(void);
char							*ko_response(void);

void							parse_options(int argc, char **argv);
int								team_name_to_id(char *name);

int								have_we_ticked(void);

void							remove_dead_players(void);

t_command_list					*dequeue_commands(void);

void							execute_command_list(t_command_list *lst);

void							handle_possible_gameover(void);

void							send_results_to_users(t_command_list *lst);

void							decrement_user_command_timers(void);

void							check_and_hatch_eggs(void);
void							enqueue_player_egg(int x, int y, int team_id);

void							socket_lookup_init(int do_close);
void							socket_lookup_add(int fd, enum e_socktype type);
void							socket_lookup_remove(int fd, int do_close);
int								socket_lookup_has(int fd, enum e_socktype type);
int								iter_next_readable_socket(void);

void							listen_for_connections(int port);
void							handle_incoming_socket_data(void);
int								get_server_fd(void);

int								get_cmdfunc_tick_delay(t_cmdfunc f);
t_cmdfunc						string_to_cmdfunc(char *string, char **arg_ptr);

t_command						*new_cmd(t_cmdfunc f);
void							free_cmd(t_command *cmd);
t_command						*string_to_command(char *string);

t_client						*new_client(int sock_fd, int id, int type);
void							free_client(t_client *client);

t_command_list					*new_cmdlist(t_command *cmd);
void							free_cmdlist(t_command_list *list);

void							ply_new_cmdqueue(t_ply_cmd_queue *q);
void							ply_free_cmdqueue(t_ply_cmd_queue *q);
int								ply_enqueue_command(
		t_ply_cmd_queue *q, t_command *cmd);
int								ply_enqueue_front(
		t_ply_cmd_queue *q, t_command *cmd);
t_command_list					*ply_dequeue_command(t_ply_cmd_queue *q);

void							initiate_handshake(int server_fd);
void							complete_handshake(int cli_fd);

void							receive_user_message(int cli_fd);

void							register_client(int sock_fd, int id, int type);
t_client						*get_client_by_id(int id);
t_client						*get_client_by_socket_fd(int sock_fd);
void							unregister_client_by_id(int id);

void							gfx_sendone(int fd, char *format, ...);
void							gfx_sendall(char *format, ...);

void							send_stringified_responses(t_command_list *lst);

void							init_tick_timer(void);
int								have_we_ticked(void);
int								get_elapsed_ticks(void);

int								perceived_direction(int d, t_player *p);
int								opposite_direction(int d);
int								direction_add(int d1, int d2);
int								direction_sub(int d1, int d2);

#endif
