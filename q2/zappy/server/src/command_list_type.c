/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:52 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:52 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "command_list_type.h"

t_command_list	*new_cmdlist(t_command *cmd)
{
	t_command_list	*holder;

	if (!(holder = malloc(sizeof(t_command_list))))
		return (NULL);
	holder->cmd = cmd;
	holder->next = NULL;
	return (holder);
}

void			free_cmdlist(t_command_list *list)
{
	t_command_list	*iter;
	t_command_list	*purger;

	purger = NULL;
	iter = NULL;
	if (!(list))
		return ;
	iter = list->next;
	while (iter)
	{
		purger = iter;
		iter = iter->next;
		free_cmd(purger->cmd);
		free(purger);
	}
	free_cmd(list->cmd);
	free(list);
}
