/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_user_message.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:13 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:13 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client_type.h"
#include "command_type.h"

#define MAX_USER_COMMAND_LENGTH 4096
#define MAX_USER_CLIENT_RECV (MAX_USER_COMMAND_LENGTH * MAX_COMMANDS)
#define GFX_BAD_COMMAND_MSG_MAX_LEN 31

char		*read_user_buffer(int cli_fd)
{
	char	buf[MAX_USER_CLIENT_RECV + 1];
	int		count;
	char	*s;

	s = NULL;
	if ((count = recv(cli_fd, buf, MAX_USER_CLIENT_RECV, 0)) > 0)
	{
		buf[count] = '\0';
		asprintf(&s, "%s", buf);
	}
	return (s);
}

static void	send_gfx_client_bad_cmd_msg(int player_id, char *msg)
{
	char	buf[GFX_BAD_COMMAND_MSG_MAX_LEN + 1];

	msg[strcspn(msg, "\n")] = '\0';
	snprintf(buf, sizeof(buf), "%s", msg);
	gfx_sendall("BAD_COMMAND %d %s\n", player_id, buf);
}

t_command	*message_extract_next_command(char *msg, char **msg_next)
{
	char		*nl;
	t_command	*cmd;

	cmd = NULL;
	if (*msg && (nl = strchr(msg, '\n')))
	{
		*nl = '\0';
		cmd = string_to_command(msg);
		*nl = '\n';
		*msg_next = nl + 1;
	}
	else
		*msg_next = strchr(msg, '\0');
	return (cmd);
}

void		enqueue_commands_from_user_message(t_client *client, char *msg)
{
	char		*msg_next;
	t_command	*cmd;

	msg_next = msg;
	while (client->cmdqueue.size <= 10 && *msg_next)
	{
		if ((cmd = message_extract_next_command(msg, &msg_next)))
		{
			cmd->player_id = client->id;
			ply_enqueue_command(&(client->cmdqueue), cmd);
			if (cmd->cmdfunc == fork_player)
				gfx_sendall("LAY_EGG %d\n", client->id);
		}
		else
			send_gfx_client_bad_cmd_msg(client->id, msg);
		msg = msg_next;
	}
}

void		receive_user_message(int cli_fd)
{
	t_client	*client;
	char		*msg;

	client = get_client_by_socket_fd(cli_fd);
	if (!(msg = read_user_buffer(cli_fd)))
		unregister_client_by_id(client->id);
	else
		enqueue_commands_from_user_message(client, msg);
	free(msg);
}
