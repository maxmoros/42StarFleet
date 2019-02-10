/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_options.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:53 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:53 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct s_opts g_opts = {
	.server_port = 0,
	.tickrate = 100,
	.world_width = 0,
	.world_height = 0,
	.initial_players_per_team = 0,
	.team_names = NULL,
};

static char *g_usage =
"Usage: ./server -p <port> -x <width> -y <height> -n <team> \
[<team>] [<team>] ... -c <nb> [-t <t>]\n\
-p port number\n\
-x world width\n\
-y world height\n\
-n team_name_1 team_name_2 ...\n\
-c number of clients authorized at the beginning of the game\n\
-t [100] time unit divider (the greater t is, the faster the game will go)\n";

static int *g_opts_keys[] = {
	['x'] = &g_opts.world_width,
	['y'] = &g_opts.world_height,
	['c'] = &g_opts.initial_players_per_team,
	['t'] = &g_opts.tickrate,
	['p'] = &g_opts.server_port,
	['n'] = (int *)&g_opts.team_names
};

static char g_badnum[] = "Option '- ' takes a positive integer argument.";

#define MAX_REASONABLE_TEAM_COUNT 64
#define BAD_OPT(msg) ({ fprintf(stderr, "%s (Try '--help')\n", msg); exit(1); })
#define COMPLAIN_NOT_POSITIVE(c) ({ g_badnum[9] = c; BAD_OPT(g_badnum); })

static void		parse_team_names(char **argv)
{
	int		i;
	char	team_name_length_errmsg[256];

	sprintf(team_name_length_errmsg,
			"Limit team names to %d characters.", MAX_TEAM_NAME_LENGTH);
	if (optarg[0] == '-')
		BAD_OPT("Team names can't start with '-'.");
	g_opts.team_names = calloc(MAX_REASONABLE_TEAM_COUNT + 1, sizeof(char *));
	i = 0;
	while (argv[optind + i - 1] && argv[optind + i - 1][0] != '-')
	{
		g_opts.team_names[i] = argv[optind + i - 1];
		if (strlen(g_opts.team_names[i]) > MAX_TEAM_NAME_LENGTH)
			BAD_OPT(team_name_length_errmsg);
		if (team_name_to_id(g_opts.team_names[i]) != i)
			BAD_OPT("Team names must be unique.");
		i++;
	}
	g_opts.teamcount = i;
	optind += i - 1;
}

int				team_name_to_id(char *name)
{
	int		i;

	i = 0;
	while (g_opts.team_names[i])
	{
		if (!strcmp(g_opts.team_names[i], name))
			return (i);
		i++;
	}
	return (-1);
}

static void		check_missing_or_excess_options(char **argv)
{
	char	required_option_keys[32];
	char	ch;
	int		i;

	i = 0;
	sprintf(required_option_keys, "p x y c n ");
	while ((ch = required_option_keys[i]))
	{
		if (g_opts_keys[(int)ch][0] != 0)
			required_option_keys[i] = ' ';
		i += 2;
	}
	if (strcmp("          ", required_option_keys))
	{
		fprintf(stderr, "Missing required opts: %s", required_option_keys);
		BAD_OPT("");
	}
	if (argv[optind] != NULL)
	{
		fprintf(stderr, "Excess arguments detected: %s\n", argv[optind]);
		BAD_OPT("");
	}
}

void			parse_options(int argc, char **argv)
{
	char	ch;

	if (argc > MAX_REASONABLE_TEAM_COUNT + 11)
		BAD_OPT("Too many arguments.");
	if (argc <= 2 || !strcmp("--help", argv[1]))
	{
		printf("%s", g_usage);
		exit(0);
	}
	while ((ch = getopt(argc, argv, "p:x:y:n:c:t:")) != -1)
	{
		if (strchr("pxyct", ch))
		{
			if ((g_opts_keys[(int)ch][0] = atoi(optarg)) <= 0)
				COMPLAIN_NOT_POSITIVE(ch);
		}
		else if (ch == 'n')
			parse_team_names(argv);
		else
			exit(1);
	}
	check_missing_or_excess_options(argv);
}
