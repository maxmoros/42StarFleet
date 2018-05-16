/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:43:19 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 14:48:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	clear_term(void)
{
	ft_putstr_fd(tgetstr("cl", NULL), 1);
}

void	actkey_remove(t_select *node)
{
	t_item		*item;

	item = node->table->list;
	ft_putstr("A\n");
	while (!(item->state & 0x02))
		item = item->next;
	ft_putstr("B\n");
	item->next->state |= 0x02;
	ft_putstr("C\n");
	remove_item(node, item);
	ft_putstr("D\n");
}
