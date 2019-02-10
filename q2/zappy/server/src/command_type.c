/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:44 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:44 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_type.h"

t_command	*new_cmd(t_cmdfunc f)
{
	t_command	*cmd;

	if (!(cmd = malloc(sizeof(*cmd))))
		return (NULL);
	cmd->cmdfunc = f;
	cmd->player_id = -1;
	cmd->args = NULL;
	cmd->response = NULL;
	return (cmd);
}

t_command	*string_to_command(char *string)
{
	t_cmdfunc	f;
	char		*args;
	t_command	*cmd;

	args = NULL;
	if (!(f = string_to_cmdfunc(string, &args)))
		return (NULL);
	if (!(cmd = new_cmd(f)))
	{
		free(args);
		return (NULL);
	}
	cmd->args = args;
	return (cmd);
}

void		free_cmd(t_command *cmd)
{
	free(cmd->args);
	free(cmd->response);
	free(cmd);
}
