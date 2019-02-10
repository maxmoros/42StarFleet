/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdfunc_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:55 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:55 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "delays.h"

int					get_cmdfunc_tick_delay(t_cmdfunc f)
{
	if (f == connect_nbr)
		return (DELAY_TIMER_CONNECT_NBR);
	if (f == inventory)
		return (DELAY_TIMER_INVENTORY);
	if (f == fork_player)
		return (DELAY_TIMER_LAY_EGG);
	if (f == incantation)
		return (DELAY_TIMER_START_INCANT);
	if (f == incantation_finish)
		return (DELAY_TIMER_FINISH_INCANT);
	return (DELAY_TIMER_DEFAULT);
}

static t_cmdfunc	string_to_cmdfunc_nullary(char *s)
{
	if (!strcmp(SERVER_STRING_ADVANCE, s))
		return (advance);
	if (!strcmp(SERVER_STRING_CONNECT_NBR, s))
		return (connect_nbr);
	if (!strcmp(SERVER_STRING_FORK, s))
		return (fork_player);
	if (!strcmp(SERVER_STRING_INCANTATION, s))
		return (incantation);
	if (!strcmp(SERVER_STRING_INVENTORY, s))
		return (inventory);
	if (!strcmp(SERVER_STRING_KICK, s))
		return (kick);
	if (!strcmp(SERVER_STRING_LEFT, s))
		return (left);
	if (!strcmp(SERVER_STRING_RIGHT, s))
		return (right);
	if (!strcmp(SERVER_STRING_SEE, s))
		return (see);
	return (NULL);
}

static t_cmdfunc	string_to_cmdfunc_unary(char *s, char **arg_ptr)
{
	size_t		len;
	size_t		max_len;
	char		*space;

	if (!(space = strchr(s, ' ')))
		return (NULL);
	*space = '\0';
	if (strcmp(SERVER_STRING_BROADCAST, s) != 0
			&& strcmp(SERVER_STRING_PUT, s) != 0
			&& strcmp(SERVER_STRING_TAKE, s) != 0)
		return (NULL);
	max_len = !strcmp(s, SERVER_STRING_BROADCAST)
		? MAX_BROADCAST_LENGTH : MAX_OBJ_NAME_LENGTH;
	len = strnlen(space + 1, max_len);
	if ((space + 1)[len] != '\0')
		return (NULL);
	asprintf(arg_ptr, "%s", space + 1);
	if (!strcmp(s, SERVER_STRING_BROADCAST))
		return (broadcast);
	if (!strcmp(s, SERVER_STRING_PUT))
		return (put);
	if (!strcmp(s, SERVER_STRING_TAKE))
		return (take);
	return (NULL);
}

t_cmdfunc			string_to_cmdfunc(char *string, char **arg_ptr)
{
	if (!strncmp(string, SERVER_STRING_TAKE, 2)
			|| !strncmp(string, SERVER_STRING_PUT, 2)
			|| !strncmp(string, SERVER_STRING_BROADCAST, 2))
		return (string_to_cmdfunc_unary(string, arg_ptr));
	return (string_to_cmdfunc_nullary(string));
}
