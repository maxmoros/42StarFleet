
modules:

    game/various: map.c, tile.c, ...

    cmdfunc_type.c, .h
    command_type.c, .h
    command_list_type.c, .h
    command_queue_type.c, .h
    client_type.c, .h
    client_map_type.c, .h

    user_commands/
    (advance, left_right, see, inventory, take, put, kick, broadcast, incantation, fork, connect_nbr).c

    gfx_clients.c
    user_clients_lookup.c
    active_socket_info.c

    command_line_options.c
    listen_for_connections.c
    handshake.c
    receive_user_message.c
    time_to_tick.c
    remove_dead_players.c
    pull_ready_commands.c
    execute_command_list.c
    game_over.c
    send_stringified_responses.c
    decrement_user_command_timers.c

    server.c


# Overview

Our program is essentially some setup, and then a while(1) loop that continuously checks for a few possible events.

### Setup

+ Parse and record the values for port, world size, team names, and initial player count. *`command_line_options.c`*
+ Start up the server listening process on the user-specified port. *`listen_for_connections.c`*
+ Create the game map and the initial player avatars. *`game/?`*

### Received a connection request from a user client:

+ Initiate the handshake. *`handshake.c`*

### Received a connection request from a graphics client:

+ Register them as a known graphics client *`gfx_clients.c`*

### After we have begun a user handshake, that user sent us a second message

+ Ask game if a body is available on that team. If so, assign the client to that body. *`handshake.c`*

### A user client with a living in-game avatar sent us a command:

+ Add any valid commands contained in the message until the client's command queue is full *`receive_user_message.c`*

### One "tick" of time has passed: *`time_to_tick.c`*

+ Remove from consideration anyone who starves to death before they can act. Tell them they died. *`remove_dead_players.c`*
+ Get list of ready-to-execute commands for remaining players. *`dequeue_commands.c`*
+ (Maybe sort, and) Run every command in the list, storing the game's response *`execute_command_list.c`, `user_commands/<various>.c`*
+ (If someone won, or if everyone died, inform the clients and end.) *`game_over.c`*
+ Report to the user clients the results of their commands. *`send_stringified_responses.c`*
+ Send a specialized report to any connected graphics clients, if they requested one. *`?.c`*
+ Free the executed commands with their args and responses.
+ Decrement the timer of the top command in every user's queue. *`decrement_user_command_timers.c`*

# types and globals

	typedef void (*t_cmdfunc)(int player_id, void *args);

	typedef struct s_client {
		int socket_fd;
		int player_id;
		t_command_queue *cmdqueue;
	} t_client;

	typedef struct s_command {
		t_cmdfunc cmdfunc;
		char *args;
		char *response;
		struct timespec timestamp; // maybe -- only for an optional but fairness-ensuring extra featureint player_id;
	} t_command;

	typedef struct s_command_list {
		t_command *cmd;
		t_command_list *next;
	} t_command_list;

	typedef struct s_command_queue {
		t_command_list *head;
		t_command_list *tail;
		int remaining_space;
		int dequeue_timer;
	} t_command_queue;

	enum e_connection_type {
		HANDSHAKE,
		USER,
		SERVER,
		GFX
	};
	
	extern struct s_opts  {
        int tickrate;
        int server_port;
        int world_width;
        int world_height;
        int initial_players_per_team;
        char **team_names;
	} g_opts;

# module details

## client_type.c

+ `t_client *new_client(int socket_fd, int player_id);`
+ `void free_client(t_client *client);`

## client_map_type.c

+ `t_client *map_get_client(t_client_map *map, int id);`
+ `void map_add_client(t_client_map *map, t_client *client);`
+ `t_client *map_remove_client(t_client_map *map, t_client *client);`

## cmdfunc_type.c

+ `int get_cmdfunc_tick_delay(t_cmdfunc f);`
+ `t_cmdfunc string_to_cmdfunc(char *s, char **arg);`

	- If the string matches a cmdfunc that takes an argument, allocate space for the argument and return a pointer to the function.
	- If it matches a cmdfunc that takes no arguments, just return the pointer.
	- If it doesn't match any valid command, return NULL.

## command_type.c

+ `t_command *new_cmd(t_cmdfunc f, int player_id);`
+ `void free_cmd(t_command *cmd);`

## command_list_type.c

+ `t_command_list *new_cmdlist(t_command *cmd);`
+ `void free_cmdlist(t_command_list *list);`

## command_queue_type.c

+ `t_command_queue *new_cmdqueue(void);`
+ `void free_cmdqueue(t_command_queue *q);`
+ `int enqueue_command(t_command_queue *q, t_command *cmd)`

	- If the queue has no space remaining, return -1.
	- If there is no `head`, make this command the `head` and the `tail`, and set the `dequeue_timer` to the proper initial delay. *command_type.c*
	- Else add a command at `tail->next`.
	- Decrement and return`remaining_space`.

+ `t_command_list *dequeue_command(t_command_queue *q)`

	- If there is nothing in the queue, return NULL.
	- Remove a `command_list` from the front of the queue.
	- Set `head` to that `command_list`'s `next` pointer.
	- Increment `remaining_space`.
	- Set `dequeue_timer` to the initial delay proper for the new `head`. *`command_type.c`*
	- Return the dequeued `command_list`.

## listen_for_connections.c

+ `void listen_for_connections(port);`

	- Get a socket in passive mode and remember that it's our server fd. *`active_socket_info.c`*

## time_to_tick.c

+ `struct timespec g_next_tick`

+ `int have_we_ticked();`

	- Get a `current_time` timespec.
	- If `g_next_tick` has never been filled, or if `current_time > g_next_tick` set `g_next_tick += (1 / t)` and return 1.
	- Else return 0.

## active_socket_info.c

	static fd_set g_handshake_fds;
	static fd_set g_user_fds;
	static fd_set g_all_fds;
	static fd_set g_gfx_fds;
	static int g_max_fd;
	static int g_server_fd;

+ `int is_connection_type(int sock_fd, enum e_connection_type type);`

	- If type is SERVER, check if equal to `g_server_fd`. Else check the corresponding `fd_set` with `FD_ISSET`.

+ `void set_connection_type(int sock_fd, enum e_connection_type type);`

	- Add `sock_fd` to `g_all_fds`.
	- If larger than `g_max_fd`, set `g_max_fd` to equal `sock_fd`.
	- If type is SERVER, set `g_server_fd`. Else add to the corresponding `fd_set` with `FD_SET`.

+ `void unset_connection_type(int sock_fd, enum e_connection_type type);`

	- Remove from the appropriate `fd_set` with `FD_CLR`.

+ `void forget_connection(int sock_fd);`

	- If `sock_fd` was equal to `g_max_fd`, find the largest remaining fd and set `g_max_fd` to that.
	- Close `sock_fd`.
	- Remove `sock_fd` every fd set.

## user_clients_lookup.c

	static int g_count;
	static size_t g_capacity
	static t_client **g_user_clients;
	static t_client_map *g_client_player_map;
	static t_client_map *g_client_socket_map;

+ `t_client **get_clients(void)`

	- Simple accessor for the clients list.

+ `void register_user_client(int socket_fd, int player_id);`

	- Remove from `handshake_fds` and add to `player_fds`. *`active_socket_info.c`*
	- Create a `t_client` with the appropriate `socket_fd` and `player_id` *`client_type.c`*
	- If `g_count` == `g_capacity`, realloc more space, increase `g_capacity` appropriately, and insert new client at index `g_count`.
	- Else find the first NULL slot and stick the new client there.
	- Increment `g_count`.
	- Add to the client hash map. *`client_map_type.c`*
	
+ `t_client *get_client_by_player_id(int player_id);`

	- Get the address of the right client object from `g_client_player_map`. Return it. *`client_map_type.c`*

+ `t_client *get_client_by_socket_fd(int socket_fd);`

	- Get the address of the right client object from `g_client_socket_map`. Return it. *`client_map_type.c`*

+ `void unregister_user_client(t_client *client);`

	- Entirely forget the connection with this socket. *active_socket_info.c*
	- Free the client and insert a NULL in its previous place in the array.
	- Decrement `g_count`.
	- Delete the corresponding entry from both `g_client_player_map` and `g_client_socket_map`. *`client_map_type.c`*

## gfx_clients.c
*Stub, mostly here as a placeholder*

	static int g_count;
	static size_t g_capacity;
	static t_gfx_client **g_gfx_clients;

+ `void register_gfx_client(int socket_fd);`

	- Realloc first if necessary.
	- Call `set_connection_type(socket_fd, GFX)`, create a `t_gfx_client` object, stick it in the array, and increment `g_count`.

+ `t_gfx_client *get_gfx_client(int socket_fd);`

	- Walk through the array to find the right one. There will never be more than a few `gfx_clients`... right?

## command_line_options.c

	struct s_opts g_opts; // declaration of `extern struct g_opts` will live here unless/until we make an `extern.c`

+ `set_game_parameters(int worldwidth, int worldheight, int initial_team_size, char **teamnames);`

	- Set `g_worldwidth` and `g_worldheight`.
	- Allocate and fill `g_teamnames`, adding a NULL as the last element.
	- Tell the game logic module how many teams there are, the size of the world, and the initial team size.

+ `int get_world_dimensions(int *width, int *height);`

	- Set the values pointed to by `width` and `height` to `g_worldwidth` and `g_worldheight`.
*Only really called by `handshake.c`, but making them our only globals would be even weirder.*

+ `int get_team_id(char *name);`

	- Search front-to-back for the first matching name and return its index, or -1 if no match is found before the final NULL.
*Few teams, relatively rarely called; time is unlikely to be a concern here.*

## handshake.c

+ `void initiate_handshake(int serv_id);`

	- Add to `all_fds` and `handshake_fds` *`active_socket_info.c`*
	- Send `"WELCOME\n"`

+ `void continue_handshake(int cli_fd);`

	- Check that the message they sent matches `valid_teamname\n` *`game_parameters.c`*
	- If they sent anything else, forget this client *`active_socket_info.c`*
	- If they named an existing team, ask the game to assign them a `player_id` and tell us how many more spots are open on that team. *`game/something`*
	- If there was at least one open spot, tell them the world size and their remaining open spots, then register them as a new client *`user_clients_lookup.c`*

+ `void send_worldsize_msg(int cli_fd);`

	- If it doesn't exist yet, first create a `static char *msg` by calling `get_world_dimensions`. *`game_parameters.c`*
	- Send the message: "$width $height\n"

## game_over.c

+ `int is_game_over(int *winning_team_id);`

	- Ask the game logic module whether the game has ended and which team won. *`game/something.c`*
	- If the game has not ended, return 0 and leave `winning_team_id` unchanged.
	- If someone has won, place the `team_id` of that team in `winning_team_id` and return 1.
	- If the game ended because everyone died, place `-1` in `winning_team_id` and return 1.


+ `void handle_game_over(void);`

	- Send some end-of-game data to the graphics clients.
	- Exit.

## receive_user_message.c

+ `void receive_user_message(int cli_fd)`

	- Get the client object *`user_clients_lookup.c`*
	- Read the message into a buffer.
	- While client's command queue is not full and the message has unexamined text remaining:
	* 	Replace the first newline with a `'\0'` and see if the resulting string matches a valid user command. *string_to_cmdfunc.c*
	* 	If so, create and enqueue a command object. *`command_type.c`, `command_queue_type.c`*
	* 	Advance the message pointer to continue checking the remainder of the buffer.

## remove_dead_players.c

+ `void remove_dead_players(void);`

	- Get a list from the game of the players who will starve to death this turn. *`game/something.c`*
	- For each dead player, get their client object, send them the message "death\n", and call `unregister_user_client` *`user_clients_lookup.c`*

## dequeue_commands.c

+ `t_command_list *dequeue_commands(t_client **user_clients, int player_count)`

	- Examine each queue accessible from the passed `user_clients` list
	- While any queue has a `dequeue_timer` of zero, remove the top command from that queue and insert it into a linked list.
	- Return the list.

## execute_command_list.c

+ `void execute_command_list(t_command_list *list)`

	- For each node in `list`, call the node's cmdfunc and store the result in that same command struct. *`user_commands/\<various>.c`*

## send_stringified_responses.c

+ `void send_stringified_responses(t_command_list *list)`

	- For each node in `list`, send the result back to the user.

## user_commands/advance.c

+ `char *advance(int player_id, void *args);`

	- Call a game function to move `player_id`'s avatar one space in the direction they are currently facing and return "ok\n".

## user_commands/right_left.c

+ `char *left(int player_id, void *args);`

	- Call a game function to change the facing of `player_id`'s avatar and return "ok\n".

+ `char *right(int player_id, void *args);`

	- Same as `left`.

## user_commands/see.c

+ `char *see(int player_id, void *args);`

	- Get the player struct and determine how far they can see.
	- Determine the right absolute direction to proceed depending on their current facing.
	- Fill a tile array outwards in a 'cone' starting at the player's location.
	- Translate that data into a string by separating the contents of each tile with spaces and separating tiles with commas. *Completely empty tiles appear as ", ," if at least one non-empty tile follows, but are omitted if followed only by other empty tiles.*
	- Return the string.

## user_commands/inventory.c

+ `char *inventory(int player_id, void *args);`

	- Get the player struct.
	- Translate the contents of their inventory and their current food status into a string, then return the string. *Format: `food 345, sibur 2, deraumere 0...` -- note the zero and the huge food count. Probably that represents `energy + food * 126` instead of just `food`.*

## user_command/put_take.c

+ `char *put(int player_id, void *args);`

	- Attempt to place the item named in `args` from the player's inventory onto their tile.
	- If the attempt fails, return "ko\n".
	- Else return "ok\n".

+ `char *take(int player_id, void *args);`

	- Attempt to take the item named in `args` from the player's current tile into their inventory.
	- If the attempt fails, return "ko\n".
	- Else return "ok\n".

## user_commands/kick.c

+ `char *kick(int player_id, void *args);`

	- Get the `player_id`'s of the occupants of the player's current tile.
	- If the current player is the only occupant , return "ko\n".
	- Else, for each other occupant besides the current player, move that player on the direction the current player is facing and return "ok\n".

## user_commands/broadcast.c

+ `char *broadcast(int player_id, void *args);`

	- Get from the game an array of `int[2]`s indicating each player and their direction relative to the current player's location.
	- For each item in this array, get the corresponding client struct and send its socket a message of the form `message <K>,<text>\n`, where `K` is the direction returned from the game, `text` is `args`, and `message` is the literal string "message".

## user_commands/incantation.c

*The pdf can be read as meaning several different things here. Our current working interpretation is: only one person starts the incantation; people other than the "chanter" can move around during the incantation; stones are consumed immediately, but only if the incantation will succeed; and if the chanter finishes the incantation alive then everyone who was originally on the square and of the right level will go up to chanter_level + 1.*

	typedef struct s_incant_args {
		int player_id;
		int *levelup_group;
		int group_size;
		int new_level;
	} t_incant_args;

+ `char *incantation_finish(int player_id, void *args);`

	- For each living player in the passed `t_incant_args`'s `levelup_group`, call a game function to raise their level to `new_level`.
	- Send the client named by `args->player_id` the message `"current level <K>\n"`, where `K` is the `t_incant_args`'s `new_level` field.
*the `player_id` passed as an argument to this function will be meaningless*

+ `char *incantation(int player_id, void *args);`

	- Check whether the player's current tile has enough of the right kind of stones to construct a totem and enough players of the correct level to begin the ritual.
	- If not, create a `t_incant_args` with a `levelup_group` containing only the calling player, a `group_size` of one, and a `new_level` of the player's current level.
	- Else create a `t_incant_args` with a `levelup_group` containing the `player_id` of every player whose level equals that of the calling player, `group_size` with the array's size, and `new_level` with the player's current level plus one.
	- Add to the player's queue an `incantation_finish` event with the constructed `t_incant_args` for 300 ticks in the future.
	- Send `"elevation in progress\n"` to the calling player.

## user_commands/fork.c

	typedef struct s_hatch_args {
		int team_id;
		int x;
		int y;
	} t_hatch_args;

+ `char *hatch(int player_id, void *args);`

	- Call a game function to create a new player at tile `x`, `y` with random facing.

+ `char *fork_player(int player_id, void *args);`

	- Maybe tell graphics clients that we laid an egg.
	- Enqueue a `hatch` event for 600 ticks in the future.
	- Send `"ok\n"` to the player.

## user_commands/nbr_connect.c

+ `char *nbr_connect(int player_id, void *args);`

	- Get "number of authorized and unauthorized connections for the team". **?**
	- Send it with a newline back to the player.

## decrement_user_command_timers.c

+ `void decrement_user_command_timers(t_client **user_clients, int player_count);`

	- For each user client, decrease by one the value associated with the top command in their command queue.
