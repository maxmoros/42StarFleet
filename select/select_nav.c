/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_nav.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:32:59 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 15:28:15 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	navkey_up(t_select *node)
{
	t_item		*item;

	item = node->table->list;
	while (!(item->state & 0x02))
		item = item->next;
	item->state &= ~(0x02);
	item->prev->state |= 0x02;
}

void	navkey_down(t_select *node)
{
	t_item		*item;

	item = node->table->list;
	while (!(item->state & 0x02))
		item = item->next;
	item->state &= ~(0x02);
	item->next->state |= 0x02;
}

void	navkey_left(t_select *node)
{
	if (node)
		;
}

void	navkey_right(t_select *node)
{
	if (node)
		;
}

void	navkey_select(t_select *node)
{
	t_item		*item;

	item = node->table->list;
	while (!(item->state & 0x02))
		item = item->next;
	if (item->state & 0x01)
		item->state &= ~(0x01);
	else
		item->state |= 0x01;
}
