/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:40 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:40 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	start_server_and_game(void)
{
	game_init(g_opts.world_width, g_opts.world_height,
			g_opts.teamcount, g_opts.initial_players_per_team);
	seed_tiles_initial_resources();
	signal(SIGPIPE, SIG_IGN);
	listen_for_connections(g_opts.server_port);
	init_tick_timer();
}

int		main(int argc, char **argv)
{
	t_command_list	*cmds;

	parse_options(argc, argv);
	start_server_and_game();
	while (1)
	{
		handle_incoming_socket_data();
		if (have_we_ticked())
		{
			gfx_sendall("TICK %d\n", get_elapsed_ticks());
			check_and_hatch_eggs();
			game_upkeep();
			remove_dead_players();
			cmds = dequeue_commands();
			execute_command_list(cmds);
			send_stringified_responses(cmds);
			free_cmdlist(cmds);
			decrement_user_command_timers();
			handle_possible_gameover();
		}
	}
}
