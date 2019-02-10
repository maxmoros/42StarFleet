/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:17 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:17 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

char	*inventory(int player_id, void *args)
{
	char		*str;
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	asprintf(&str, "{%s %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d}\n",
			SERVER_STRING_FOOD,
			p->count[FOOD] * ENERGY_PER_FOOD + p->energy,
			p->count[LINEMATE],
			p->count[DERAUMERE],
			p->count[SIBUR],
			p->count[MENDIANE],
			p->count[PHIRAS],
			p->count[THYSTAME]);
	gfx_sendall("INVENTORY %d\n", player_id);
	return (str);
}
