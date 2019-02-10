NAME		= server

CC			= gcc
CFLAGS		+= -Wall -Werror -Wextra
INC_FLAGS	= -I inc
DEBUG		= #-g

GAME_SRC	= $(addprefix game/, $(GAME_FILES))
GAME_FILES	= map_creation.c \
			  player_movement.c \
			  map_tile_movement.c \
			  map_tile_to_player_funcs.c \
			  player_creation.c \
			  player_death.c \
			  player_data_api.c \
			  player_data_api_2.c \
			  player_empty_list_funcs.c \
			  game_init.c \
			  game_upkeep.c \
			  resource_spawning.c \
			  winning_and_losing.c \
			  direction.c \

USRCMD_SRC	= $(addprefix user_commands/, $(USRCMD_FILES))
USRCMD_FILES= advance.c \
			  broadcast.c \
			  connect_nbr.c \
			  fork_player.c \
			  incantation.c \
			  inventory.c \
			  kick.c \
			  left_right.c \
			  put_take.c \
			  see.c \
			  simple_responses.c \

FILES		= active_socket_info.c \
			  cmdfunc_type.c \
			  command_type.c \
			  command_line_options.c \
			  command_list_type.c \
			  command_player_queue_type.c \
			  listen_for_connections.c \
			  receive_user_message.c \
			  clients_lookup.c \
			  handshake.c \
			  decrement_user_command_timers.c \
			  execute_command_list.c \
			  remove_dead_players.c \
			  game_over.c \
			  send_stringified_responses.c \
			  time_to_tick.c \
			  dequeue_commands.c \
			  client_type.c \
			  ascii_visuals.c \
			  hatch_queue.c \
			  gfx_event_messages.c \
			  iterators.c \

SRC			= $(addprefix src/, $(FILES) $(GAME_SRC) $(USRCMD_SRC))

MAIN		= src/server.c

TESTMAIN	= test/testmain.c
TESTS		= $(wildcard test/test_*.c) test/helpers.c

# ---------------------------------------------------------------------------- #

BLUE	= \033[38;5;105;1m
GREEN	= \033[1;32m
NO_COLOR    = \033[m

all: $(NAME)

$(NAME): $(SRC) $(INC) $(MAIN)
	mkdir -p ../bin
	@printf "%b" "$(GREEN)Compiling: $(BLUE)$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -o $(NAME) $(MAIN) $(SRC)
	cp $(NAME) ../bin/

clean:
	@printf "Cleaning up $(NAME)...\n"

fclean: clean
	@rm -f ../bin/$(NAME)
	@rm -f test_$(NAME)
	@rm -f $(NAME)

re: fclean all

test: CFLAGS += -Wno-error -Wno-unused-parameter -Wno-unused-variable
test: test_$(NAME)
test_$(NAME): $(SRC) $(INC) $(TESTMAIN) $(TESTS)
	@printf "%b" "$(GREEN)Compiling: $(BLUE)test_$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -Itest -o test_$(NAME) $(TESTMAIN) $(TESTS) $(SRC)

norm:
	@printf "%b" "$(GREEN)$(NAME): Checking Norm...\n$(NO_COLOR)"
	norminette $(SRC) $(INC) $(MAIN)

dev: CFLAGS += -Wno-error -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=undefined
dev: all

ascii: CFLAGS += -DASCII_ANIMATIONS
ascii: dev

.PHONY: clean fclean all re test norm dev ascii
