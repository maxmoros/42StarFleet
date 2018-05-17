/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_nav.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:32:59 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 20:41:23 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	navkey(t_select *node, char dir)
{
	t_item		*item;
	int			i;
	int			j;

	item = node->table->list;
	j = 0;
	while (!(item->state & 0x02) && ++j)
		item = item->next;
	item->state &= ~(0x02);
	if ((dir == 0x43 || dir == 0x44) && !(i = 0))
		if ((dir == 0x43 && j + node->table->rows > node->elements &&
			j / node->table->rows < node->table->cols - 1) || (dir == 0x44 &&
			j < node->table->rows && j > node->elements % node->table->rows))
			item = node->table->list->prev;
		else
			while (i++ < node->table->rows)
			{
				item = (dir == 0x43 ? item->next : item->prev);
				if (item == node->table->list && i != node->table->rows)
					i += node->table->cols * node->table->rows - node->elements;
			}
	else
		item = (dir == 0x41 ? item->prev : item->next);
	item->state |= 0x02;
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
